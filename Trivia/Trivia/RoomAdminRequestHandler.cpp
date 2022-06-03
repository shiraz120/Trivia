#include "RoomAdminRequestHandler.h"

/*
this function will create a new RoomAdminHandler object
input: user, room, handlerFactory
output: none
*/
RoomAdminHandler::RoomAdminHandler(const LoggedUser user, Room& room, RequestHandlerFactory& handlerFactory) : RoomHandler(user, room, handlerFactory)
{
}

/*
this function will delete a RoomAdminHandler object
input: none
output: none
*/
RoomAdminHandler::~RoomAdminHandler()
{
}

/*
this function will check if a request is relevant using the request id
input: request
output: none
*/
bool RoomAdminHandler::isRequestRelevant(RequestInfo request)
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
RequestResult RoomAdminHandler::handleRequest(RequestInfo request)
{
	switch (request.id)
	{
	case CLOSE_ROOM_REQUEST:
		return closeRoom(request);
		break;
	case GET_ROOM_STATE_REQUEST:
		return getRoomState(request);
		break;
	case START_GAME_REQUEST:
		return startGame(request);
		break;
	}
}

/*
this function will return the room state and the room data
input: request
output: requestResult
*/
RequestResult RoomAdminHandler::getRoomState(RequestInfo request) const
{
	RequestResult response = RoomHandler::getRoomData(request);
	response.newHandler = new RoomAdminHandler(m_user, m_room, m_handlerFactory);
	return response;
}

/*
this function will close a room
input: request
output: RequestResult
*/
RequestResult RoomAdminHandler::closeRoom(RequestInfo request) const
{
	RequestResult response;
	CloseRoomResponse data;
	data.status = STATUS_SUCCESS;
	try {
		m_roomManager.deleteRoom(m_room.getMetaData().id);
	}
	catch (statusException& se)
	{
		data.status = se.statusRet();
	}
	response.response = JsonResponsePacketSerializer::serializeResponse<CloseRoomResponse>(data, CLOSE_ROOM_RESPONSE);
	if (data.status == STATUS_SUCCESS)
		response.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	else
		response.newHandler = m_handlerFactory.createRoomAdminRequestHandler(m_user, m_room);
	return response;
}


/*
this function will start a game
input: request
output: RequestResult
*/
RequestResult RoomAdminHandler::startGame(RequestInfo request) const
{
	return RequestResult();
}