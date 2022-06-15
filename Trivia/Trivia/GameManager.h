#pragma once
#include "Game.h"
#include "dataBase.h"
#include "Room.h"
class GameManager
{
public:
	GameManager(IDatabase* db);
	~GameManager();
	Game createGame(const Room room);
	void deleteGame(const LoggedUser userInRoom);
	void removeUser(const LoggedUser user);
	void updateUserDataInDataBase(const LoggedUser user);
	
private:
	Game& getGameByUser(const LoggedUser user);
	IDatabase* m_database;
	vector<Game> m_games;
	std::mutex m_gameMutex;
};