#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
class RequestHandlerFactory;
class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(const LoggedUser user, RequestHandlerFactory& handlerFactory);
	virtual ~MenuRequestHandler();
	bool isRequestRelevant(const RequestInfo request) const override;
	RequestResult handleRequest(const RequestInfo request) override;

private:
	LoggedUser m_user;
	RoomManager& m_roomManager;
	StatisticsManager& m_statisticsManager;
	RequestHandlerFactory& m_handlerFactory;
	RequestResult getRandomMassage(const RequestInfo request) const;
	RequestResult signout(const RequestInfo request) const;
	RequestResult getRooms(const RequestInfo request) const;
	RequestResult getPlayersInRoom(const RequestInfo request) const;
	RequestResult getPersonalStats(const RequestInfo request) const;
	RequestResult getHighScore(const RequestInfo request) const;
	RequestResult joinRoom(const RequestInfo request) const;
	RequestResult createRoom(const RequestInfo request) const;
};