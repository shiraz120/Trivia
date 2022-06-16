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
	data.status = STATUS_SUCCESS;
	try
	{
		m_roomManager.removeUserFromARoom(m_room.getMetaData().id, m_user);
	}
	catch (statusException& e)
	{
		data.status = e.statusRet();
	}
	response.response = JsonResponsePacketSerializer::serializeResponse<LeaveRoomResponse>(data, LEAVE_GAME_RESPONSE);
	response.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	return response;
}

/*
this function will return the room state and the room data
input: request
output: requestResult
*/
RequestResult RoomMemberHandler::getRoomState(const RequestInfo request) const
{
	GetRoomStateResponse response = RoomHandler::getRoomData(request);
	RequestResult data;
	data.response = JsonResponsePacketSerializer::serializeResponse<GetRoomStateResponse>(response, GET_ROOM_STATE_RESPONSE);
	if (response.status == STATUS_SUCCESS && response.hasGameBegun == ACTIVE)
		data.newHandler = m_handlerFactory.createGameRequestHandler(m_user);
	else if (response.status == STATUS_SUCCESS)
		data.newHandler = m_handlerFactory.createRoomMemberRequestHandler(m_user);
	else
		data.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	return data;
}

/*
this function will check if a request is relevant using the request id
input: request 
output: none
*/
bool RoomMemberHandler::isRequestRelevant(const RequestInfo request) const
{
	if (request.id == GET_ROOM_STATE_REQUEST || request.id == LEAVE_ROOM_REQUEST)
		return true;
	return false;
}

/*
this function will handle the request
input: request
output: RequestResult
*/
RequestResult RoomMemberHandler::handleRequest(const RequestInfo request)
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
