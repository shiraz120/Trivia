#include "Room.h"

/*
this function will init Room object
input: roomData
output: none
*/
Room::Room(RoomData roomData, LoggedUser admin) : m_metadata(roomData)
{
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
this function will add new user if the size of the vector isnt bigger than the maxPlayers
input: newUser
output: none
*/
void Room::addUser(const LoggedUser newUser)
{
	if (m_users.size() < m_metadata.maxPlayers)
		m_users.push_back(newUser);
}

/*
this function will remove a user from the vector if the user exists
input: existingUser
output: none
*/
void Room::removeUser(const LoggedUser existingUser)
{
	for(auto it = m_users.begin(); it != m_users.end(); it++)
		if(it->getUsername() == existingUser.getUsername())
			m_users.erase(it);
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
