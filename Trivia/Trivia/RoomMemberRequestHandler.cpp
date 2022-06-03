#include "RoomMemberRequestHandler.h"

/*
this function will create a new RoomMemberHandler object
input: user, room, handlerFactory
output: none
*/
RoomMemberHandler::RoomMemberHandler(const LoggedUser user, Room& room, RequestHandlerFactory& handlerFactory) : RoomHandler(user, room, handlerFactory)
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
	return RequestResult();
}

/*
this function will return the room state and the room data
input: request
output: requestResult
*/
RequestResult RoomMemberHandler::getRoomState(RequestInfo request) const
{
	RequestResult response = RoomHandler::getRoomData(request);
	response.newHandler = new RoomMemberHandler(m_user, m_room, m_handlerFactory);
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
