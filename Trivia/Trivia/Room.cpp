#include "Room.h"

/*
this function will init a room by copy all variables from one room to another
input: other
output: room refernce
*/
Room::Room(const Room& copyFrom)
{
	*this = copyFrom;
}

/*
this function will init Room object
input: roomData
output: none
*/
Room::Room(const RoomData roomData, const LoggedUser admin) 
{
	m_metadata = roomData;
	std::lock_guard<std::mutex> usersListLock(usersMutex);
	m_users.push_back(admin);
}

/*
this function will delete a room object
input: none
output: none
*/
Room::~Room()
{
}

/*
this function will set the activity of the room
input: active
output: none
*/
void Room::setActivity(const int active)
{
	m_metadata.isActive = active;
}

/*
this function will add new user if the size of the vector isnt bigger than the maxPlayers
input: newUser
output: none
*/
void Room::addUser(const LoggedUser newUser)
{
	for (int i = 0; i < m_users.size(); i++)
	{
		if(m_users[i].getUsername() == newUser.getUsername())
			throw statusException(STATUS_USER_ALREADY_IN_ROOM);
	}
	if (m_users.size() < m_metadata.maxPlayers)
	{
		std::lock_guard<std::mutex> usersListLock(usersMutex);
		m_users.push_back(newUser);
	}
	else
		throw statusException(STATUS_ROOM_IS_FULL);
}

/*
this function will remove a user from the vector if the user exists
input: existingUser
output: none
*/
void Room::removeUser(const LoggedUser existingUser)
{
	for(auto it = m_users.begin(); it != m_users.end(); it++)
		if (it->getUsername() == existingUser.getUsername())
		{
			std::unique_lock<std::mutex> usersListLock(usersMutex);
			m_users.erase(it);
			usersListLock.unlock();
			return;
		}
}

/*
this function will return the room meta data
input: none
output: the room meta data
*/
RoomData Room::getMetaData() const
{
	return m_metadata;
}

/*
this function will return all users in the vector 
input: none
output: all users that exist
*/
std::vector<string> Room::getAllUsers() const
{
	std::vector<string> users;
	for (auto it : m_users)
		users.push_back(it.getUsername());
	return users;
}

/*
this function will copy all variables from one room to another
input: other
output: room refernce
*/
Room& Room::operator=(const Room& other)
{
	if (this != &other)
	{
		this->m_metadata = other.m_metadata;
		for (auto it : other.m_users)
			this->m_users.push_back(LoggedUser(it.getUsername()));
	}
	return *this;
}
