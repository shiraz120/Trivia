#include "MenuRequestHandler.h"
MenuRequestHandler::MenuRequestHandler(LoggedUser user, RoomManager& roomManager, StatisticsManager& statisticsManager, RequestHandlerFactory& handlerFactory) : m_user(user), m_roomManager(roomManager), m_statisticsManager(statisticsManager), m_handlerFactory(handlerFactory)
{
}
MenuRequestHandler::~MenuRequestHandler()
{
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo request)
{
	return false;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo request)
{
	return RequestResult();
}

