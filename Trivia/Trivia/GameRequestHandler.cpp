#include "GameRequestHandler.h"

GameHandler::GameHandler(const LoggedUser user, RequestHandlerFactory& handlerFactory) : m_handlerFactory(handlerFactory), m_gameManager(handlerFactory.getGameManager()), m_user(user.getUsername())
{
	std::vector<RoomData> rooms = m_handlerFactory.getRoomManager().getRooms();
	std::vector<string> players;
	for (RoomData room : rooms)
	{
		try
		{
			players = m_handlerFactory.getRoomManager().getAllUsersFromSpecificRoom(room.id);
		}
		catch (statusException&)
		{
		}
		if (std::count(players.begin(), players.end(), user.getUsername()) == 1)
		{
			m_game = m_gameManager.createGame(Room(room, LoggedUser(players[0])));
		}
	}
}

GameHandler::~GameHandler()
{
}

bool GameHandler::isRequestRelevant(const RequestInfo request) const
{
	if (request.id == LEAVE_ROOM_REQUEST || request.id == SUBMIT_ANSWER_REQUEST || request.id == GET_GAME_RESULTS_REQUEST || request.id == GET_QUESTION_REQUEST)
		return true;
	return false;
}

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
			if (answers[i] == correctAnswer)
				data.answers = map<unsigned int, std::vector<string>>{ { i, answers } };
		}
	}
	catch (statusException& e)
	{
		data.status = e.statusRet();
	}
	response.response = JsonResponsePacketSerializer::serializeResponse<GetQuestionResponse>(data, GET_QUESTION_RSPONSE);
	response.newHandler = m_handlerFactory.createGameRequestHandler(m_user);
	return response;
}

RequestResult GameHandler::submitAnswer(const RequestInfo request)  
{
	RequestResult response;
	SubmitAnswerResponse data;
	SubmitAnswerRequest userData = JsonRequestPacketDeserializer::deserializeRequest<SubmitAnswerRequest>(request.buffer);
	data.status = STATUS_SUCCESS;
	try
	{
		vector<string> answers = m_game.getQuestionForUser(m_user).getPossibleAnswers();
		string correctAnswer = m_game.getQuestionForUser(m_user).getCorrentAnswer();
		m_game.submitAnswer(m_user, m_game.getQuestionForUser(m_user).getPossibleAnswers()[userData.answerId]);
		for (int i = 0; i < answers.size(); i++)
		{
			if (answers[i] == correctAnswer)
				data.correctAnswerId = i;
		}
		m_gameManager.updateUserDataInDataBase(m_user);
	}
	catch (statusException& e)
	{
		data.status = e.statusRet();
	}
	response.response = JsonResponsePacketSerializer::serializeResponse<SubmitAnswerResponse>(data, SUBMIT_ANSWER_RSPONSE); // not creating error response because even if there is any error within the data base it isnt relevant for the user, it just wont update the user stats in the data base
	response.newHandler = m_handlerFactory.createGameRequestHandler(m_user);
	return response;
}

RequestResult GameHandler::getGameResults(const RequestInfo request) const
{
	RequestResult response;
	GetGameResultsResponse data;
	vector<string> allUsersInRequestedRoom;
	if (m_game.checkIfGameOver())
	{
		data.status = STATUS_GAME_OVER;
		data.results = m_game.getAllPlayersData();
		m_gameManager.deleteGame(m_user);
		m_handlerFactory.getRoomManager().deleteRoom(getRoomId());
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

RequestResult GameHandler::leaveGame(const RequestInfo request) const
{
	RequestResult response;
	LeaveGameResponse data;
	data.status = STATUS_SUCCESS;
	std::vector<std::string> allUsersInRequestedRoom;
	try
	{
		m_gameManager.removeUser(m_user);
		m_handlerFactory.getRoomManager().removeUserFromARoom(getRoomId(), m_user);
		m_gameManager.updateUserDataInDataBase(m_user);
	}
	catch (statusException& e)
	{
		data.status = e.statusRet();
	}
	response.response = JsonResponsePacketSerializer::serializeResponse<LeaveGameResponse>(data, LEAVE_GAME_RESPONSE); // not creating error response because even if there is any error within the data base it isnt relevant for the user, it just wont update the user stats in the data base
	response.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	return response;
}
