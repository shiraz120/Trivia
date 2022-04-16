#include "LoggedUser.h"
#include "RoomData.h"
#include <vector>

class Room
{
public:
	Room() = default;
	Room(RoomData roomData, LoggedUser admin);
	~Room();
	void addUser(const LoggedUser newUser);
	void removeUser(const LoggedUser existingUser);
	RoomData getMetaData() const;
	std::vector<string> getAllUsers() const;
	
private:
	RoomData m_metadata;
	std::vector<LoggedUser> m_users;
};