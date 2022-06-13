#include "GameRequestHandler.h"

GameHandler::GameHandler(const LoggedUser user, RequestHandlerFactory& handlerFactory) : m_handlerFactory(handlerFactory), m_gameManager(handlerFactory.getGameManager()), m_user(user.getUsername())
{
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

RequestResult GameHandler::handleRequest(const RequestInfo request) const
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

RequestResult GameHandler::getQuestion(const RequestInfo request) const
{
	return RequestResult();
}

RequestResult GameHandler::submitAnswer(const RequestInfo request) const
{
	return RequestResult();
}

RequestResult GameHandler::getGameResults(const RequestInfo request) const
{
	return RequestResult();
}

RequestResult GameHandler::leaveGame(const RequestInfo request) const
{
	return RequestResult();
}
