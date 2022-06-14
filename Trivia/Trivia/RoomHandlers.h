#pragma once
#include "RequestHandlerFactory.h"
#include "IRequestHandler.h"

class RequestHandlerFactory;
class RoomHandler
{
public:
	RoomHandler(const LoggedUser user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory);
	~RoomHandler();
	RequestResult getRoomData(const RequestInfo request) const;
protected:
	LoggedUser m_user;
	Room m_room;
	RequestHandlerFactory& m_handlerFactory;
	RoomManager& m_roomManager;
};