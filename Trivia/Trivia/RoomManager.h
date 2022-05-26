#pragma once
#include "Room.h"
#include <iostream>
#include <map>
#include <mutex>

class RoomManager
{
public:
	RoomManager();
	~RoomManager();
	void createRoom(const LoggedUser user, RoomData& room);
	void deleteRoom(const unsigned id);
	unsigned int getRoomState(const unsigned id);
	std::vector<RoomData> getRooms();
	std::vector<std::string> getAllUsersFromSpecificRoom(const unsigned id);
	void addUserToRoom(const unsigned id, LoggedUser username);
	
private:
	std::map<unsigned int, Room> m_rooms;
	std::mutex roomMutex;
};
