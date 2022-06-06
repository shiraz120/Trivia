#include "RoomMemberRequestHandler.h"

/*
this function will create a new RoomMemberHandler object
input: user, room, handlerFactory
output: none
*/
RoomMemberHandler::RoomMemberHandler(const LoggedUser user, RequestHandlerFactory& handlerFactory) : RoomHandler(user, handlerFactory.getRoomManager()), m_handlerFactory(handlerFactory)
{
}

/*
this function will delete a RoomMemberHandler object
input: none
output: none
*/
RoomMemberHandler::~RoomMemberHandler()
{
}

/*
this function will remove a user from the current room
input: request
output: requestResult
*/
RequestResult RoomMemberHandler::leaveRoom(const RequestInfo request) const
{
	RequestResult response;
	LeaveRoomResponse data;
	ErrorResponse error;
	data.status = STATUS_SUCCESS;
	try
	{
		m_roomManager.removeUserFromARoom(m_room.getMetaData().id, m_user);
		response.response = JsonResponsePacketSerializer::serializeResponse<LeaveRoomResponse>(data, LEAVE_GAME_RESPONSE);
	}
	catch (std::exception& e)
	{
		error.message = e.what();
		response.response = JsonResponsePacketSerializer::serializeResponse<ErrorResponse>(error, ERROR_RESPONSE);
		data.status = STATUS_FAILED;
	}
	response.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	return response;
}

/*
this function will return the room state and the room data
input: request
output: requestResult
*/
RequestResult RoomMemberHandler::getRoomState(RequestInfo request) const
{
	RequestResult response = RoomHandler::getRoomData(request);
	response.newHandler = m_handlerFactory.createRoomMemberRequestHandler(m_user);
	return response;
}

/*
this function will check if a request is relevant using the request id
input: request 
output: none
*/
bool RoomMemberHandler::isRequestRelevant(const RequestInfo request)
{
	if (request.id == CLOSE_ROOM_REQUEST || request.id == START_GAME_REQUEST || request.id == LEAVE_ROOM_REQUEST)
		return true;
	return false;
}

/*
this function will handle the request
input: request
output: RequestResult
*/
RequestResult RoomMemberHandler::handleRequest(RequestInfo request)
{
	switch (request.id)
	{
	case LEAVE_ROOM_REQUEST:
		return leaveRoom(request);
		break;
	case GET_ROOM_STATE_REQUEST:
		return getRoomState(request);
		break;
	}
}
