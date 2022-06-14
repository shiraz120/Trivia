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

private:
	IDatabase* m_database;
	vector<Game> m_games;
	std::mutex m_gameMutex;
};