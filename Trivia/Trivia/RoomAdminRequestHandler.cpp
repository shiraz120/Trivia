#include "RoomAdminRequestHandler.h"

bool RoomAdminHandler::isRequestRelevant(RequestInfo request)
{
	if (request.id == CLOSE_ROOM_REQUEST || request.id == START_GAME_REQUEST || request.id == LEAVE_ROOM_REQUEST)
		return true;
	return false;
}

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
		//add requestHandlerFactory usage
	return response;
}

RequestResult RoomAdminHandler::startGame(RequestInfo request) const
{
	return RequestResult();
}

RequestResult RoomAdminHandler::getRoomState(RequestInfo request) const
{
	return RequestResult();
}
