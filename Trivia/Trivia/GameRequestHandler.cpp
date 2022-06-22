#include "GameRequestHandler.h"

/*
this function will create a new GameHandler object
input: user, handlerFactory
output: none
*/
GameHandler::GameHandler(const LoggedUser user, RequestHandlerFactory& handlerFactory) : m_handlerFactory(handlerFactory), m_gameManager(handlerFactory.getGameManager()), m_user(user.getUsername()), m_lastTimeAnswered(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())), m_game(handlerFactory.getGameManager().getGameByUser(user))
{
}

/*
this function will remove a GameHandler object
input: none
output: none
*/
GameHandler::~GameHandler()
{
}

/*
this function will check if a request is relevant
input: request
output: if the request is relevant or not
*/
bool GameHandler::isRequestRelevant(const RequestInfo request) const
{
	if (request.id == LEAVE_GAME_REQUEST || request.id == SUBMIT_ANSWER_REQUEST || request.id == GET_GAME_RESULTS_REQUEST || request.id == GET_QUESTION_REQUEST)
		return true;
	return false;
}

/*
this function will handle a request and return a result
input: request
output: RequestResult
*/
RequestResult GameHandler::handleRequest(const RequestInfo request) 
{
	switch (request.id)
	{
	case LEAVE_GAME_REQUEST:
		return leaveGame(request);
		break;
	case SUBMIT_ANSWER_REQUEST:
		return submitAnswer(request);
		break;
	case GET_GAME_RESULTS_REQUEST:
		return getGameResults(request);
		break;
	case GET_QUESTION_REQUEST:
		return getQuestion(request);
		break;
	}
}

/*
this function will receive a room id from the room manager and return it
input: none
output: roomId
*/
unsigned int GameHandler::getRoomId() const
{
	RoomManager& roomManager = m_handlerFactory.getRoomManager();
	vector<RoomData> rooms = roomManager.getRooms();
	for (RoomData room : rooms)
	{
		vector<string> players = roomManager.getAllUsersFromSpecificRoom(room.id);
		if (std::find(players.begin(), players.end(), m_user.getUsername()) != players.end())
			return room.id;
	}
}

/*
this function will get the next question for m_user and send it in RequestResult
input: request
output: RequestResult
*/
RequestResult GameHandler::getQuestion(const RequestInfo request)
{
	RequestResult response;
	GetQuestionResponse data;
	data.status = STATUS_THERE_ARE_STILL_QUESTIONS;
	std::vector<std::string> allUsersInRequestedRoom;
	try
	{
		Question question = m_game.getQuestionForUser(m_user);
		string correctAnswer = question.getCorrentAnswer();
		vector<string> answers = question.getPossibleAnswers();
		data.question = question.getQuestion();
		for (unsigned int i = 0; i < answers.size(); i++)
		{
			data.answers[i] = answers[i];
		}
	}
	catch (statusException& e)
	{
		data.status = e.statusRet();
		data.answers[0] = "";
		data.answers[1] = "";
		data.answers[2] = "";
		data.answers[3] = "";
		data.question = "";
	}
	response.response = JsonResponsePacketSerializer::serializeResponse<GetQuestionResponse>(data, GET_QUESTION_RSPONSE);
	response.newHandler = m_handlerFactory.createGameRequestHandler(m_user);
	return response;
}

/*
this function will receive a request and check if the user answer is correct or not and return the currect answer index
input: request
output: RequestResult
*/
RequestResult GameHandler::submitAnswer(const RequestInfo request)  
{
	RequestResult response;
	SubmitAnswerResponse data;
	SubmitAnswerRequest userData = JsonRequestPacketDeserializer::deserializeRequest<SubmitAnswerRequest>(request.buffer);
	clock_t timeNow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	data.status = STATUS_SUCCESS;
	try
	{
		Question question = m_game.getQuestionForUser(m_user);
		vector<string> answers = question.getPossibleAnswers();
		string correctAnswer = question.getCorrentAnswer();
		for (int i = 0; i < answers.size(); i++)
		{
			if (answers[i] == correctAnswer)
				data.correctAnswerId = i;
		}
		m_game.submitAnswer(m_user, question.getPossibleAnswers()[userData.answerId]);
		m_game.updateAvgTime(m_user, float(timeNow - m_lastTimeAnswered));
		m_gameManager.updateUserData(m_user, m_game.getPlayerGameData(m_user), false);
		m_lastTimeAnswered = timeNow;
	}
	catch (statusException& e)
	{
		data.status = e.statusRet();
	}
	response.response = JsonResponsePacketSerializer::serializeResponse<SubmitAnswerResponse>(data, SUBMIT_ANSWER_RSPONSE); // not creating error response because even if there is any error within the data base it isnt relevant for the user, it just wont update the user stats in the data base
	response.newHandler = m_handlerFactory.createGameRequestHandler(m_user);
	return response;
}

/*
this function will receive a request and return the game results if the game is over
input: request
output: RequestResult
*/
RequestResult GameHandler::getGameResults(const RequestInfo request) 
{
	RequestResult response;
	GetGameResultsResponse data;
	vector<string> allUsersInRequestedRoom;
	if (m_gameManager.checkIfGameOver(m_user))
	{
		data.status = STATUS_GAME_OVER;
		m_gameManager.updateUserData(m_user, m_game.getPlayerGameData(m_user), true); // update user game results when the game is over
		data.results = m_gameManager.getAllPlayersData(m_game.getPlayerGameData(m_user), m_user);
		//m_gameManager.deleteGame(m_user);
		try
		{
			m_handlerFactory.getRoomManager().deleteRoom(getRoomId());
		}
		catch(statusException&) // only catching and not changing the data status, even if the room doesnt exist its not relevant for the user so there is no point on giving the user that information
		{ }
	}
	else
	{
		data.status = STATUS_GAME_NOT_OVER;
		data.results = {};
	}
	response.response = JsonResponsePacketSerializer::serializeResponse<GetGameResultsResponse>(data, GET_GAME_RESULTS_RSPONSE);
	if(data.status == STATUS_GAME_OVER)
		response.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	else
		response.newHandler = m_handlerFactory.createGameRequestHandler(m_user);
	return response;
}

/*
this function will receive a request and remove a m_user from the room and from the game he is currently part of
input: request
output: RequestResult
*/
RequestResult GameHandler::leaveGame(const RequestInfo request)
{
	RequestResult response;
	LeaveGameResponse data;
	data.status = STATUS_SUCCESS;
	try
	{
		m_gameManager.updateUserData(m_user, m_game.getPlayerGameData(m_user), true); // update user game results when the user leaves the game
		m_gameManager.removeUser(m_user);
		m_handlerFactory.getRoomManager().removeUserFromARoom(getRoomId(), m_user);
	}
	catch (statusException& e)
	{
		data.status = e.statusRet();
	}
	response.response = JsonResponsePacketSerializer::serializeResponse<LeaveGameResponse>(data, LEAVE_GAME_RESPONSE); // not creating error response because even if there is any error within the data base it isnt relevant for the user, it just wont update the user stats in the data base
	response.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	return response;
}
