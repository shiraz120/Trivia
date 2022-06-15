#include "GameManager.h"

GameManager::GameManager(IDatabase* db) : m_database(db)
{
}

GameManager::~GameManager()
{
}

void GameManager::removeUser(const LoggedUser user)
{
	getGameByUser(user).removeUser(user);
}

Game GameManager::createGame(const Room room)
{
	std::list<Question> questions;
	try
	{
		questions = m_database->getQuestions(room.getMetaData().numOfQuestionsInGame);
	}
	catch (std::exception& e)
	{
		/* if there is a problem with data base, lets asume it got deleted etc the function will init the list with our questions */
		questions = { Question("", "", "", "", ""), Question("", "", "", "", ""), Question("", "", "", "", ""), Question("", "", "", "", ""), Question("", "", "", "", ""), Question("", "", "", "", ""), Question("", "", "", "", ""), Question("", "", "", "", ""), Question("", "", "", "", ""), Question("", "", "", "", "") }; 
	}
	Game newGame(room.getAllUsers(), std::vector<Question>(questions.begin(), questions.end()));
	std::unique_lock<std::mutex> gameLock(m_gameMutex);
	m_games.push_back(newGame);
	gameLock.unlock();
	return newGame;
}

void GameManager::deleteGame(const LoggedUser userInRoom)
{
	for (int i = 0; i < m_games.size(); i++)
	{
		vector<string> players = m_games[i].getPlayersInRoom();
		if (std::count(players.begin(), players.end(), userInRoom.getUsername()))
		{
			std::unique_lock<std::mutex> gameLock(m_gameMutex);
			m_games.erase(m_games.begin(), m_games.begin() + i);
			gameLock.unlock();
		}
	}
}

void GameManager::updateUserDataInDataBase(const LoggedUser user)
{
	string username = user.getUsername();
	GameData playerData = getGameByUser(user).getPlayerGameData(user);
	m_database->updateNumOfCorrectAnswers(username, playerData.correctAnswerCount);
	m_database->updateNumOfPlayersGames(username);
	m_database->updateNumOfTotalAnswers(username, playerData.correctAnswerCount + playerData.wrongAnswerCount);
	m_database->updatePlayerAverageAnswerTime(username, playerData.averageAnswerTime);
}

Game& GameManager::getGameByUser(const LoggedUser user)
{
	for (int i = 0; i < m_games.size(); i++)
	{
		vector<string> players = m_games[i].getPlayersInRoom();
		if (std::count(players.begin(), players.end(), user.getUsername()))
			return m_games[i];
	}
}


