#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class IRequestHandler;
class RoomMemberHandler : IRequestHandler
{
public:
	bool isRequestRelevant(RequestInfo request) override;
	RequestResult handleRequest(RequestInfo request) override;
private:
	RequestResult leaveRoom(RequestInfo request) const;
	RequestResult getRoomState(RequestInfo request) const;
	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;
};