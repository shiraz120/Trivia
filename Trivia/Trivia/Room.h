#pragma once
#include "LoggedUser.h"
#include "RoomData.h"
#include "statusException.h"
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
	std::vector<string> getAllUsers() const;

	/*ADDED FUNCTIONS - NOT IN THE DESIGN*/
	void setActivity(int active);
	RoomData getMetaData() const;
	Room& operator=(const Room& other);
	
private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
	std::mutex usersMutex;
};