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
bool RoomAdminHandler::isRequestRelevant(const RequestInfo request) const
{
	if (request.id == CLOSE_ROOM_REQUEST || request.id == START_GAME_REQUEST || request.id == GET_ROOM_STATE_REQUEST)
		return true;
	return false;
}

/*
this function will handle the request
input: request
output: RequestResult
*/
RequestResult RoomAdminHandler::handleRequest(const RequestInfo request)
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
RequestResult RoomAdminHandler::getRoomState(const RequestInfo request) const
{
	/* passes null and not gameHandler because its meaningless to change the handler to game handler when we are talking about the admin of the room, the change to gameHandler will happened when the admin starts the game */
	GetRoomStateResponse response = RoomHandler::getRoomData(request);
	RequestResult data;
	data.newHandler = m_handlerFactory.createRoomAdminRequestHandler(m_user);
	data.response = JsonResponsePacketSerializer::serializeResponse<GetRoomStateResponse>(response, GET_ROOM_STATE_RESPONSE);
	return data;
}

/*
this function will close a room
input: request
output: RequestResult
*/
RequestResult RoomAdminHandler::closeRoom(const RequestInfo request) const
{
	RequestResult response;
	CloseRoomResponse data;
	data.status = STATUS_SUCCESS;
	try {
		m_roomManager.deleteRoom(m_room.getMetaData().id);
	}
	catch (statusException& e)
	{
		data.status = e.statusRet();
	}
	response.response = JsonResponsePacketSerializer::serializeResponse<CloseRoomResponse>(data, CLOSE_ROOM_RESPONSE);
	response.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	return response;
}


/*
this function will start a game
input: request
output: RequestResult
*/
RequestResult RoomAdminHandler::startGame(const RequestInfo request) const
{
	RequestResult response;
	StartGameResponse data;
	data.status = STATUS_SUCCESS;
	try {
		m_roomManager.setRoomActivity(m_room.getMetaData().id, ACTIVE);
		m_handlerFactory.getGameManager().createGame(m_room);
	}
	catch (statusException& e)
	{
		data.status = e.statusRet();
	}
	response.response = JsonResponsePacketSerializer::serializeResponse<StartGameResponse>(data, START_GAME_RESPONSE);
	response.newHandler = m_handlerFactory.createGameRequestHandler(m_user);
	return response;
}
