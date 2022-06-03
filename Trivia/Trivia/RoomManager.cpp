#include "RoomManager.h"

RoomManager::RoomManager()
{
}

RoomManager::~RoomManager()
{
}

void RoomManager::createRoom(const LoggedUser user, RoomData& room)
{
	unsigned int lastestKey = 0;
	if (m_rooms.size() != 0)
		lastestKey = m_rooms.rbegin()->first;
	room.id = lastestKey + 1; // because that we dont receive the room id when the manager is requested to create a new room the function will just take the lastest id and insert to it 1 for the new room id
	Room newRoom(room, user);
	std::lock_guard<std::mutex> roomListLock(roomMutex);
	m_rooms.insert(std::pair<unsigned int, Room>(room.id, newRoom));
}

void RoomManager::deleteRoom(const unsigned id)
{
	if (m_rooms.find(id) == m_rooms.end())
		throw statusException(STATUS_ROOM_DOESNT_EXIST);
	std::lock_guard<std::mutex> roomListLock(roomMutex);
	m_rooms.erase(id);
}

unsigned int RoomManager::getRoomState(const unsigned id)
{
	if (m_rooms.find(id) == m_rooms.end())
		throw statusException(STATUS_ROOM_DOESNT_EXIST);
	return m_rooms[id].getMetaData().isActive;
}

std::vector<RoomData> RoomManager::getRooms()
{
	std::vector<RoomData> activeRooms;
	for (auto it = m_rooms.begin(); it != m_rooms.end(); it++)
		if (it->second.getMetaData().isActive == ACTIVE)
			activeRooms.push_back(it->second.getMetaData());
	return activeRooms;
}

std::vector<std::string> RoomManager::getAllUsersFromSpecificRoom(const unsigned id)
{
	if (m_rooms.find(id) == m_rooms.end())
		throw statusException(STATUS_ROOM_DOESNT_EXIST);
	return m_rooms[id].getAllUsers();
}

void RoomManager::addUserToRoom(const unsigned id, LoggedUser username)
{
	if (m_rooms.find(id) == m_rooms.end())
		throw statusException(STATUS_ROOM_DOESNT_EXIST);
	m_rooms[id].addUser(username);
}

Room& RoomManager::getRoom(const int id)
{
	return m_rooms[id]; // use the function only in join/ create room so the room exists
}
