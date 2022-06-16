#pragma once
#include "IRequestHandler.h"

class RoomHandler : public IRequestHandler
{
public:
	RoomHandler(const LoggedUser user, RoomManager& roomManager);
	~RoomHandler();
	GetRoomStateResponse getRoomData(const RequestInfo request) const;
protected:
	LoggedUser m_user;
	Room m_room;
	RoomManager& m_roomManager;
};