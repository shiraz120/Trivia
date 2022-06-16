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
		questions = { Question("What is the order of the colors in Russia's flag?", "White Blue Red", "White Red Blue", "Red Blue White", "Blue White Red"), Question("What is the first programing language?", "Fortran", "Algol", "C", "Assembly"), Question("which south american country has the capital city of quito?", "Ecuador", "Colombia", "Paraguay", "Guyana"), Question("which of the following is not an organ in the human body?", "Ulna", "Eye", "Pancreas", "Gallbladder"), Question("what is the fastest land animal?", "cheetah", "giraffe", "tiger", "wolf"), Question("what does the roman numeral D stand for?", "500", "100", "50", "1000"), Question("when did pablo picasso die?", "1973", "1676", "1447", "1890"), Question("which of these numbers has a 1 in the thousadnths place?", "3.3412", "3.1234", "3.2341", "3.4123"), Question("where is manila?", "the philippines", "italy", "singapore", "spain"), Question("what is a common graph algorithm?", "depth first", "merge sort", "binary search", "radix sort") }; 
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
this function will update the user data in the data base and in the vector of games
input: user, data
output: none
*/
void GameManager::updateUserData(const LoggedUser user, const GameData data)
{
	string username = user.getUsername();
	getGameByUser(user).updateUserData(user, data);
	m_database->updateNumOfCorrectAnswers(username, data.correctAnswerCount);
	m_database->updateNumOfPlayersGames(username);
	m_database->updateNumOfIncorrectAnswers(username, data.wrongAnswerCount);
	m_database->updatePlayerAverageAnswerTime(username, data.averageAnswerTime);
}

/*
this function will check if the game is over - if all the players answered all the questions, the game is over
input: user
output: bool - if the game is over or not
*/
bool GameManager::checkIfGameOver(const LoggedUser user)
{
	for (string player : getGameByUser(user).getPlayersInRoom())
	{
		if (getGameByUser(user).getPlayerGameData(LoggedUser(player)).currentQuestion.getQuestion() != NO_MORE_QUESTIONS)
			return false;
	}
	return true;
}


/*
this function will return all players game results
input: data, user
output: playersData
*/
vector<PlayerResults> GameManager::getAllPlayersData(const GameData data, const LoggedUser user)
{
	vector<PlayerResults> results;
	for (string player : getGameByUser(user).getPlayersInRoom())
	{
		GameData data = getGameByUser(user).getPlayerGameData(LoggedUser(player));
		results.push_back(PlayerResults{player, data.correctAnswerCount, data.wrongAnswerCount, data.averageAnswerTime});
	}
	return results;
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

