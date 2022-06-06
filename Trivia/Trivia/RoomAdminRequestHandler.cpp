#include "RoomAdminRequestHandler.h"

/*
this function will create a new RoomAdminHandler object
input: user, room, handlerFactory
output: none
*/
RoomAdminHandler::RoomAdminHandler(const LoggedUser user, RequestHandlerFactory& handlerFactory) : RoomHandler(user, handlerFactory.getRoomManager()), m_handlerFactory(handlerFactory)
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
	response.newHandler = m_handlerFactory.createRoomAdminRequestHandler(m_user);
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
	ErrorResponse error;
	data.status = STATUS_SUCCESS;
	try {
		m_roomManager.deleteRoom(m_room.getMetaData().id);
		response.response = JsonResponsePacketSerializer::serializeResponse<CloseRoomResponse>(data, CLOSE_ROOM_RESPONSE);
	}
	catch (std::exception& e)
	{
		error.message = e.what();
		response.response = JsonResponsePacketSerializer::serializeResponse<ErrorResponse>(error, ERROR_RESPONSE);
		data.status = STATUS_FAILED;
	}
	if (data.status == STATUS_SUCCESS)
		response.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	else
		response.newHandler = m_handlerFactory.createRoomAdminRequestHandler(m_user);
	return response;
}


/*
this function will start a game
input: request
output: RequestResult
*/
RequestResult RoomAdminHandler::startGame(RequestInfo request) const
{
	RequestResult response;
	StartGameResponse data;
	ErrorResponse error;
	data.status = STATUS_SUCCESS;
	try {
		m_roomManager.setRoomActivity(m_room.getMetaData().id, ACTIVE);
		response.response = JsonResponsePacketSerializer::serializeResponse<StartGameResponse>(data, START_GAME_RESPONSE);
	}
	catch (std::exception& e)
	{
		error.message = e.what();
		response.response = JsonResponsePacketSerializer::serializeResponse<ErrorResponse>(error, ERROR_RESPONSE);
		data.status = STATUS_FAILED;
	}
	response.newHandler = m_handlerFactory.createRoomAdminRequestHandler(m_user); // change in v4
	return RequestResult();
}
