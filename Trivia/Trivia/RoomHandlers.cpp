#include "RoomHandlers.h"
/*
this function will create a RoomHandler object
input: user, room, handlerFactory
output: none
*/
RoomHandler::RoomHandler(const LoggedUser user, Room& room, RoomManager& roomManager) : m_user(user), m_room(room), m_roomManager(roomManager)
{
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
