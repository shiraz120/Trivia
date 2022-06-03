#pragma once
#include "IRequestHandler.h"

class RoomHandler
{
public:
	RoomHandler(const LoggedUser user, Room& room, RoomManager& roomManager);
	~RoomHandler();
	RequestResult getRoomData(RequestInfo request) const;
protected:
	LoggedUser m_user;
	Room& m_room;
	RoomManager& m_roomManager;
};