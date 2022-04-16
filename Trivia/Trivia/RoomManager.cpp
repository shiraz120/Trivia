#include "RoomManager.h"

RoomManager::RoomManager()
{
}

RoomManager::~RoomManager()
{
}

void RoomManager::createRoom(LoggedUser user, RoomData room)
{
	Room newRoom(room, user);
	m_rooms.insert({ room.id, newRoom });
}

void RoomManager::deleteRoom(unsigned id)
{
	m_rooms.erase(id);
}

unsigned int RoomManager::getRoomState(unsigned id)
{
	return m_rooms[id].getMetaData().isActive;
}

std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> activeRooms;
	for (auto it : m_rooms)
		if (it.second.getMetaData().isActive == ACTIVE)
			activeRooms.push_back(it.second.getMetaData());
	return activeRooms;
}
