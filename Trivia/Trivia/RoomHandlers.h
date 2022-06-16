#pragma once
#include "IRequestHandler.h"

class RoomHandler : public IRequestHandler
{
public:
	RoomHandler(const LoggedUser user, RoomManager& roomManager);
	virtual ~RoomHandler();
	GetRoomStateResponse getRoomData(const RequestInfo request) const;
protected:
	LoggedUser m_user;
	Room m_room;
	RoomManager& m_roomManager;
};