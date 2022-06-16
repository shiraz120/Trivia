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
	bool checkIfGameOver(const LoggedUser user);
	void updateUserData(const LoggedUser user, const GameData data);
	vector<PlayerResults> getAllPlayersData(const GameData data, const LoggedUser user);
	
private:
	Game& getGameByUser(const LoggedUser user);
	IDatabase* m_database;
	vector<Game> m_games;
	std::mutex m_gameMutex;
};