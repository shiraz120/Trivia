#include "RoomHandlers.h"
/*
this function will create a RoomHandler object
input: user, room, handlerFactory
output: none
*/
RoomHandler::RoomHandler(const LoggedUser user, RoomManager& roomManager) : m_user(user), m_roomManager(roomManager)
{
	std::vector<RoomData> rooms = m_roomManager.getRooms();
	std::vector<string> players;
	for (RoomData room : rooms)
	{
		try
		{
			players = m_roomManager.getAllUsersFromSpecificRoom(room.id);
		}
		catch(statusException&)
		{ }
		if (std::count(players.begin(), players.end(), user.getUsername()) == 1)
		{
			m_room = Room(room, LoggedUser(players[0]));
			for (int i = 1; i < players.size(); i++)
			{
				m_room.addUser(players[i]);
			}
		}
	}
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
GetRoomStateResponse RoomHandler::getRoomData(const RequestInfo request) const
{
	GetRoomStateResponse responseData;
	responseData.status = STATUS_SUCCESS;
	try {
		responseData.hasGameBegun = m_roomManager.getRoomState(m_room.getMetaData().id); // if exception thrown it means that the room doesnt exist anymore
		responseData.questionCount = m_room.getMetaData().numOfQuestionsInGame;
		responseData.answerTimeout = m_room.getMetaData().timePerQuestion;
		responseData.players = m_room.getAllUsers();
	}
	catch (statusException& e)
	{
		responseData.questionCount = 0;
		responseData.answerTimeout = 0;
		responseData.players = {};
		responseData.status = e.statusRet();
	}
	return responseData;
}
