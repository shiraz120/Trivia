#pragma once
#include "LoggedUser.h"
#include "RoomData.h"
#include <iostream>
#include <vector>
#include <mutex>

class Room
{
public:
	Room() = default;
	Room(const Room& copyFrom);
	Room(const RoomData roomData, const LoggedUser admin);
	~Room();
	void addUser(const LoggedUser newUser);
	void removeUser(const LoggedUser existingUser);
	RoomData getMetaData() const;
	std::vector<string> getAllUsers() const;
	Room& operator=(const Room& other);
	
private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
	std::mutex usersMutex;
};