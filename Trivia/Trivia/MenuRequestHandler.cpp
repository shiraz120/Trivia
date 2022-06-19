#include "MenuRequestHandler.h"
/*
this function will create a new menuRequestHandler object
input: user, handlerFactory
output: none
*/
MenuRequestHandler::MenuRequestHandler(const LoggedUser user, RequestHandlerFactory& handlerFactory) : m_user(user), m_roomManager(handlerFactory.getRoomManager()), m_statisticsManager(handlerFactory.getStatisticsManager()), m_handlerFactory(handlerFactory)
{
}

/*
this function will remove a menuRequestHandler object
input: none
output: none
*/
MenuRequestHandler::~MenuRequestHandler()
{
}

/*
this function will check if a request is relevant
input: request
output: bool - is relevant or not
*/
bool MenuRequestHandler::isRequestRelevant(const RequestInfo request) const
{
	if (GET_RANDOM_MASSAGE_REQUEST == request.id || CREATE_ROOM_REQUEST == request.id || request.id == JOIN_ROOM_REQUEST || request.id == GET_ROOMS_REQUEST || request.id == GET_PLAYERS_IN_ROOM_REQUEST || request.id == GET_PERSONAL_STATS_REQUEST || request.id == GET_HIGH_SCORE_REQUEST || request.id == SIGN_OUT_REQUEST)
		return true;
	return false;
}

/*
this function will handle a request by using the request id
input: request
output: the request result
*/
RequestResult MenuRequestHandler::handleRequest(const RequestInfo request)
{
	switch (request.id)
	{
	case CREATE_ROOM_REQUEST:
		return createRoom(request);
		break;
	case JOIN_ROOM_REQUEST:
		return joinRoom(request);
		break;
	case SIGN_OUT_REQUEST:
		return signout(request);
		break;
	case GET_ROOMS_REQUEST:
		return getRooms(request);
		break;
	case GET_PLAYERS_IN_ROOM_REQUEST:
		return getPlayersInRoom(request);
		break;
	case GET_PERSONAL_STATS_REQUEST:
		return getPersonalStats(request);
		break;
	case GET_HIGH_SCORE_REQUEST:
		return getHighScore(request);
		break;
	case GET_RANDOM_MASSAGE_REQUEST:
		return getRandomMassage(request);
		break;
	}
}

RequestResult MenuRequestHandler::getRandomMassage(const RequestInfo request) const
{
	RequestResult data;
	getRandomMassageResponse response;
	response.massage = "hello world";
	data.response = JsonResponsePacketSerializer::serializeResponse<getRandomMassageResponse>(response, GET_RANDOM_MASSAGE_RESPONSE);
	data.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	return data;
}

/*
this function will logout a user
input: request
output: requestResult
*/
RequestResult MenuRequestHandler::signout(const RequestInfo request) const
{
	RequestResult response;
	LogoutResponse data;
	data.status = STATUS_SUCCESS;
	try {
		m_handlerFactory.getLoginManager().logout(m_user.getUsername());
	}
	catch (statusException& e)
	{
		data.status = e.statusRet();
	}
	response.response = JsonResponsePacketSerializer::serializeResponse<LogoutResponse>(data, LOGOUT_RESPONSE);
	if (data.status == STATUS_SUCCESS)
		response.newHandler = m_handlerFactory.createLoginRequestHandler();
	else
		response.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	return response;
}

/*
this function will get all the rooms that exist
input: request
output: requestResult
*/
RequestResult MenuRequestHandler::getRooms(const RequestInfo request) const
{
	RequestResult response;
	GetRoomsResponse data;
	std::vector<RoomData> rooms = m_roomManager.getRooms();
	data.status = STATUS_SUCCESS;
	data.rooms = rooms;
	response.response = JsonResponsePacketSerializer::serializeResponse<GetRoomsResponse>(data, GET_ROOMS_RESPONSE);
	response.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	return response;
}

/*
this function will get all the players connected to a requested room
input: request
output: requestResult
*/
RequestResult MenuRequestHandler::getPlayersInRoom(const RequestInfo request) const
{
	RequestResult response;
	GetPlayersInRoomRequest roomID = JsonRequestPacketDeserializer::deserializeRequest<GetPlayersInRoomRequest>(request.buffer);
	GetPlayersInRoomResponse data;
	std::vector<std::string> allUsersInRequestedRoom;  
	try
	{
		allUsersInRequestedRoom = m_roomManager.getAllUsersFromSpecificRoom(roomID.roomId);
	}
	catch (statusException&)
	{
		allUsersInRequestedRoom = {};
	}
	data.players = allUsersInRequestedRoom;
	response.response = JsonResponsePacketSerializer::serializeResponse<GetPlayersInRoomResponse>(data, GET_PLAYERS_IN_ROOM_RESPONSE);
	response.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	return response;
}

/*
this function will get the personal stats of a user
input: request
output: requestResult
*/
RequestResult MenuRequestHandler::getPersonalStats(const RequestInfo request) const
{
	RequestResult response;
	getPersonalStatsResponse data;
	data.status = STATUS_SUCCESS;
	try {
		data.statistics = m_statisticsManager.getUserStatistics(m_user.getUsername());
	}
	catch (statusException& e)
	{
		data.status = e.statusRet();
	}
	if (data.status == STATUS_DB_PROBLEM)
		response.response = JsonResponsePacketSerializer::serializeResponse<ErrorResponse>(ErrorResponse{ DATA_BASE_PROBLEM }, ERROR_RESPONSE);
	else
		response.response = JsonResponsePacketSerializer::serializeResponse<getPersonalStatsResponse>(data, GET_PERSONAL_STATS_RESPONSE);	
	response.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	return response;
}

/*
this function will get the top 5 top users and their scores
input: request
output: requestResult
*/
RequestResult MenuRequestHandler::getHighScore(const RequestInfo request) const
{
	RequestResult response;
	getHighScoreResponse data;
	data.status = STATUS_SUCCESS;
	try {
		data.statistics = m_statisticsManager.getHighScore();
	}
	catch (statusException& e)
	{
		data.status = e.statusRet();
	}
	if (data.status == STATUS_DB_PROBLEM)
		response.response = JsonResponsePacketSerializer::serializeResponse<ErrorResponse>(ErrorResponse{ DATA_BASE_PROBLEM }, ERROR_RESPONSE);
	else
		response.response = JsonResponsePacketSerializer::serializeResponse<getHighScoreResponse>(data, GET_HIGH_SCORE_RESPONSE);
	response.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	return response;
}

/*
this function will log a user into a room
input: request
output: requestResult
*/
RequestResult MenuRequestHandler::joinRoom(const RequestInfo request) const
{
	RequestResult response;
	JoinRoomRequest roomData = JsonRequestPacketDeserializer::deserializeRequest<JoinRoomRequest>(request.buffer);
	JoinRoomResponse data;
	data.status = STATUS_SUCCESS;
	try{
		m_roomManager.addUserToRoom(roomData.roomId, m_user);
	}
	catch (statusException& e)
	{
		data.status = e.statusRet();
	}
	response.response = JsonResponsePacketSerializer::serializeResponse<JoinRoomResponse>(data, JOIN_ROOM_RESPONSE);
	if (data.status == STATUS_SUCCESS)
		response.newHandler = m_handlerFactory.createRoomMemberRequestHandler(m_user); 
	else
		response.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	return response;
}

/*
this function will create a new room
input: request
output: requestResult
*/
RequestResult MenuRequestHandler::createRoom(const RequestInfo request) const
{
	RequestResult response;
	CreateRoomResponse data;
	CreateRoomRequest roomData = JsonRequestPacketDeserializer::deserializeRequest<CreateRoomRequest>(request.buffer);
	RoomData roomMetaData;
	roomMetaData.id = 0;
	roomMetaData.isActive = NOT_ACTIVE; // not_active means that the game didnt start yet
	roomMetaData.maxPlayers = roomData.maxUsers;
	roomMetaData.name = roomData.roomName;
	roomMetaData.numOfQuestionsInGame = roomData.questionCount;
	roomMetaData.timePerQuestion = roomData.answerTimeout;
	m_roomManager.createRoom(m_user, roomMetaData);
	data.status = roomMetaData.id;
	response.response = JsonResponsePacketSerializer::serializeResponse<CreateRoomResponse>(data, CREATE_ROOM_RESPONSE);
	response.newHandler = m_handlerFactory.createRoomAdminRequestHandler(m_user); 
	return response;
}
