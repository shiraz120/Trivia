#pragma once
#include "Game.h"
#include "dataBase.h"
#include "Room.h"
class GameManager
{
public:
	Game createGame(Room room);
	void deleteGame();

private:
	IDatabase* m_database;
	vector<Game> m_games;
};