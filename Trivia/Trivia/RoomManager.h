#include "Room.h"
#include <map>

class RoomManager
{
public:
	RoomManager();
	~RoomManager();
	void createRoom(LoggedUser user, RoomData room);
	void deleteRoom(unsigned id);
	unsigned int getRoomState(unsigned id);
	std::vector<RoomData> getRooms();

private:
	std::map<unsigned int, Room> m_rooms;
};