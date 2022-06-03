#include "MenuRequestHandler.h"
MenuRequestHandler::MenuRequestHandler(LoggedUser user, RoomManager& roomManager, StatisticsManager& statisticsManager, RequestHandlerFactory& handlerFactory) : m_user(user), m_roomManager(roomManager), m_statisticsManager(statisticsManager), m_handlerFactory(handlerFactory)
{
}

MenuRequestHandler::~MenuRequestHandler()
{
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo request)
{
	if (CREATE_ROOM_REQUEST == request.id || request.id == JOIN_ROOM_REQUEST || request.id == GET_ROOMS_REQUEST || request.id == GET_PLAYERS_IN_ROOM_REQUEST || request.id == GET_PERSONAL_STATS_REQUEST || request.id == GET_HIGH_SCORE_REQUEST || request.id == SIGN_OUT_REQUEST)
		return true;
	return false;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo request)
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
	}
}

RequestResult MenuRequestHandler::signout(const RequestInfo request)
{
	RequestResult response;
	LogoutResponse data;
	data.status = STATUS_SUCCESS;
	try {
		m_handlerFactory.getLoginManager().logout(m_user.getUsername());
	}
	catch (statusException& se)
	{
		data.status = se.statusRet();
	}
	response.response = JsonResponsePacketSerializer::serializeResponse<LogoutResponse>(data, LOGOUT_RESPONSE);
	if (data.status == STATUS_SUCCESS)
		response.newHandler = m_handlerFactory.createLoginRequestHandler();
	else
		response.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
	return response;
}

RequestResult MenuRequestHandler::getRooms(const RequestInfo request)
{
	RequestResult response;
	GetRoomsResponse data;
	std::vector<RoomData> rooms = m_roomManager.getRooms();
	if (rooms.size() == 0)
		data.status = STATUS_NO_ROOMS;
	else
		data.status = STATUS_SUCCESS;
	data.rooms = rooms;
	response.response = JsonResponsePacketSerializer::serializeResponse<GetRoomsResponse>(data, GET_ROOMS_RESPONSE);
	response.newHandler = new MenuRequestHandler(m_user, m_roomManager, m_statisticsManager, m_handlerFactory);
	return response;
}

RequestResult MenuRequestHandler::getPlayersInRoom(const RequestInfo request)
{
	RequestResult response;
	GetPlayersInRoomRequest roomID = JsonRequestPacketDeserializer::deserializeRequest<GetPlayersInRoomRequest>(request.buffer);
	GetPlayersInRoomResponse data;
	std::vector<std::string> allUsersInRequestedRoom;  
	try {
		allUsersInRequestedRoom = m_roomManager.getAllUsersFromSpecificRoom(roomID.roomId);
		data.players = allUsersInRequestedRoom;
	}
	catch (statusException& se)
	{
		data.players = {}; // means there are no players, because the room doesnt exist
	}
	response.response = JsonResponsePacketSerializer::serializeResponse<GetPlayersInRoomResponse>(data, GET_PLAYERS_IN_ROOM_RESPONSE);
	response.newHandler = new MenuRequestHandler(m_user, m_roomManager, m_statisticsManager, m_handlerFactory);
	return response;
}

RequestResult MenuRequestHandler::getPersonalStats(const RequestInfo request)
{
	RequestResult response;
	getPersonalStatsResponse data;
	data.status = STATUS_SUCCESS;
	try {
		data.statistics = m_statisticsManager.getUserStatistics(m_user.getUsername());
	}
	catch (dataBaseException& dbe)
	{
		data.status = STATUS_DB_PROBLEM;
	}
	catch (statusException& se)
	{
		data.status = se.statusRet();
	}
	response.response = JsonResponsePacketSerializer::serializeResponse<getPersonalStatsResponse>(data, GET_PERSONAL_STATS_RESPONSE);
	response.newHandler = new MenuRequestHandler(m_user, m_roomManager, m_statisticsManager, m_handlerFactory);
	return response;
}

RequestResult MenuRequestHandler::getHighScore(const RequestInfo request)
{
	RequestResult response;
	getHighScoreResponse data;
	data.status = STATUS_SUCCESS;
	try {
		data.statistics = m_statisticsManager.getHighScore();
	}
	catch (dataBaseException& dbe)
	{
		data.status = STATUS_DB_PROBLEM;
	}
	catch (statusException& se)
	{
		data.status = se.statusRet();
	}
	response.response = JsonResponsePacketSerializer::serializeResponse<getHighScoreResponse>(data, GET_HIGH_SCORE_RESPONSE);
	response.newHandler = new MenuRequestHandler(m_user, m_roomManager, m_statisticsManager, m_handlerFactory);
	return response;
}

RequestResult MenuRequestHandler::joinRoom(const RequestInfo request)
{
	RequestResult response;
	JoinRoomRequest roomData = JsonRequestPacketDeserializer::deserializeRequest<JoinRoomRequest>(request.buffer);
	JoinRoomResponse data;
	data.status = STATUS_SUCCESS;
	try{
		m_roomManager.addUserToRoom(roomData.roomId, m_user);
	}
	catch (statusException& se)
	{
		data.status = se.statusRet();
	}
	response.response = JsonResponsePacketSerializer::serializeResponse<JoinRoomResponse>(data, JOIN_ROOM_RESPONSE);
	response.newHandler = new MenuRequestHandler(m_user, m_roomManager, m_statisticsManager, m_handlerFactory);
	return response;
}

RequestResult MenuRequestHandler::createRoom(const RequestInfo request)
{
	RequestResult response;
	CreateRoomResponse data;
	CreateRoomRequest roomData = JsonRequestPacketDeserializer::deserializeRequest<CreateRoomRequest>(request.buffer);
	RoomData roomMetaData;
	roomMetaData.id = 0;
	roomMetaData.isActive = true;
	roomMetaData.maxPlayers = roomData.maxUsers;
	roomMetaData.name = roomData.roomName;
	roomMetaData.numOfQuestionsInGame = roomData.questionCount;
	roomMetaData.timePerQuestion = roomData.answerTimeout;
	m_roomManager.createRoom(m_user, roomMetaData);
	data.status = roomMetaData.id;
	response.response = JsonResponsePacketSerializer::serializeResponse<CreateRoomResponse>(data, CREATE_ROOM_RESPONSE);
	response.newHandler = new MenuRequestHandler(m_user, m_roomManager, m_statisticsManager, m_handlerFactory);
	return response;
}
