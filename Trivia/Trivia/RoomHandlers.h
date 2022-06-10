#pragma once
#include "IRequestHandler.h"

class RoomHandler
{
public:
	RoomHandler(const LoggedUser user, RoomManager& roomManager);
	~RoomHandler();
	RequestResult getRoomData(const RequestInfo request) const;
protected:
	LoggedUser m_user;
	Room m_room;
	RoomManager& m_roomManager;
};