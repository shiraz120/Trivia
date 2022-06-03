#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
class RequestHandlerFactory;
class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(const LoggedUser user, RequestHandlerFactory& handlerFactory);
	virtual ~MenuRequestHandler();
	bool isRequestRelevant(RequestInfo request) override;
	RequestResult handleRequest(RequestInfo request) override;

private:
	LoggedUser m_user;
	RoomManager& m_roomManager;
	StatisticsManager& m_statisticsManager;
	RequestHandlerFactory& m_handlerFactory;
	RequestResult signout(const RequestInfo request);
	RequestResult getRooms(const RequestInfo request);
	RequestResult getPlayersInRoom(const RequestInfo request);
	RequestResult getPersonalStats(const RequestInfo request);
	RequestResult getHighScore(const RequestInfo request);
	RequestResult joinRoom(const RequestInfo request);
	RequestResult createRoom(const RequestInfo request);
};