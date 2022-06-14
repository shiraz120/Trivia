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
	for (Game game : m_games)
	{
		vector<string> players = game.getPlayersInRoom();
		if (std::count(players.begin(), players.end(), userInRoom.getUsername()))
		{
			std::lock_guard<std::mutex> gameLock(m_gameMutex);
			m_games.erase(std::remove(m_games.begin(), m_games.end(), game), m_games.end());
			return;
		}
	}
}

