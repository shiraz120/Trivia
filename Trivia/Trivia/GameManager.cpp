#include "GameManager.h"

/*
this function will create a gameManager object
input: db
output: none
*/
GameManager::GameManager(IDatabase* db) : m_database(db)
{
}

/*
this function will delete a gameManager object
input: none
output: none
*/
GameManager::~GameManager()
{
}

/*
this function will remove a user from a room
input: user
output: none
*/
void GameManager::removeUser(const LoggedUser user)
{
	getGameByUser(user).removeUser(user);
}

/*
this function will create a game
input: room
output: newGame
*/
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

/*
this function will delete a game
input: userInRoom
output: none
*/
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

/*
this function will update the user data in the data base
input: user
output: none
*/
void GameManager::updateUserDataInDataBase(const LoggedUser user)
{
	string username = user.getUsername();
	GameData playerData = getGameByUser(user).getPlayerGameData(user);
	m_database->updateNumOfCorrectAnswers(username, playerData.correctAnswerCount);
	m_database->updateNumOfPlayersGames(username);
	m_database->updateNumOfIncorrectAnswers(username, playerData.wrongAnswerCount);
	m_database->updatePlayerAverageAnswerTime(username, playerData.averageAnswerTime);
}

/*
this function will return a refrence to a game that the requested user is part of
input: user
output: game refrence
*/
Game& GameManager::getGameByUser(const LoggedUser user)
{
	for (int i = 0; i < m_games.size(); i++)
	{
		vector<string> players = m_games[i].getPlayersInRoom();
		if (std::count(players.begin(), players.end(), user.getUsername()))
			return m_games[i];
	}
}


