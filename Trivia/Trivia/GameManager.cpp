#include "GameManager.h"

GameManager::GameManager(IDatabase* db) : m_database(db)
{
}

GameManager::~GameManager()
{
}

Game GameManager::createGame(const Room room)
{
	std::list<Question> questions = m_database->getQuestions(room.getMetaData().numOfQuestionsInGame);
	Game newGame(room.getAllUsers(), std::vector<Question>(questions.begin(), questions.end()));
	std::unique_lock<std::mutex> gameLock(m_gameMutex);
	m_games.push_back(newGame);
	gameLock.unlock();
	return newGame;
}

void GameManager::deleteGame(const LoggedUser userInRoom)
{
	for (int i = 0; i < m_games.size(); i ++)
	{
		vector<string> players = m_games[i].getPlayersInRoom();
		if (std::count(players.begin(), players.end(), userInRoom.getUsername()))
		{
			std::unique_lock<std::mutex> gameLock(m_gameMutex);
			m_games.erase(m_games.begin() + i);
			gameLock.unlock();
		}
	}
}

