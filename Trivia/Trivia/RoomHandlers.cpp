#include "RoomHandlers.h"
/*
this function will create a RoomHandler object
input: user, room, handlerFactory
output: none
*/
RoomHandler::RoomHandler(const LoggedUser user, RoomManager& roomManager) : m_user(user), m_roomManager(roomManager)
{
	std::vector<RoomData> rooms = m_roomManager.getRooms();
	std::vector<string> players;
	for (RoomData room : rooms)
	{
		players = m_roomManager.getAllUsersFromSpecificRoom(room.id);
		if (std::count(players.begin(), players.end(), user.getUsername()))
		{
			m_room = Room(room, LoggedUser(players[0]));
		}
	}
}

/*
this function will remove a RoomHandler object
input: none
output: none
*/
RoomHandler::~RoomHandler()
{
}

/*
this function will get the room data
input: request
output: result
*/
RequestResult RoomHandler::getRoomData(RequestInfo request) const
{
	GetRoomStateResponse responseData;
	RequestResult data;
	responseData.answerTimeout = m_room.getMetaData().timePerQuestion;
	responseData.hasGameBegun = m_room.getMetaData().isActive;
	responseData.players = m_room.getAllUsers();
	responseData.status = STATUS_SUCCESS;
	data.response = JsonResponsePacketSerializer::serializeResponse<GetRoomStateResponse>(responseData, GET_ROOM_STATE_RESPONSE);
	return data;
}
