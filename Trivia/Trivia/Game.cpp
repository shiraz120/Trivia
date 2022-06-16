#include "Game.h"

/*
this function will create an empty game object
input: none
output: none
*/
Game::Game()
{
}

/*
this function will create a game object
input: players, questions
output: none
*/
Game::Game(const vector<string> players, const vector<Question> questions) : m_questions(questions)
{
	m_questions.push_back(Question(NO_MORE_QUESTIONS, "", "", "", ""));
	for (string player : players)
	{
		m_players.insert({ LoggedUser(player), GameData{m_questions[0], 0, 0, 0} });
	}
}

/*
this function will remove a game object
input: none
output: none
*/
Game::~Game()
{
}

/*
this function will return the current question of the user
input: user
output: currentQuestion
*/
Question Game::getQuestionForUser(const LoggedUser user) 
{
	if (m_players[user].currentQuestion.getQuestion() == NO_MORE_QUESTIONS)
		throw statusException(STATUS_NO_MORE_QUESTIONS);
	Question currentQuestion = m_players[user].currentQuestion;
	for (int i = 0; i < m_questions.size(); i++ )
	{
		if (m_questions[i].getQuestion() == m_players[user].currentQuestion.getQuestion())
		{
			if ((i + 1) < m_questions.size())
				m_players[user].currentQuestion = m_questions[i + 1];
		}
	}
	return currentQuestion;
}

/*
this function will check if a requested user answer is correct or not and change the gameData of that user
input: user, answer
output: none
*/
void Game::submitAnswer(const LoggedUser user, const string answer)
{
	if (m_players[user].currentQuestion.getCorrentAnswer() == answer)
		m_players[user].correctAnswerCount += 1;
	else
		m_players[user].wrongAnswerCount += 1;
}

/*
this function will remove a requested user from a m_players
input: user
output: none
*/
void Game::removeUser(const LoggedUser user)
{
	for (auto it : m_players)
		if (it.first.getUsername() == user.getUsername())
		{
			m_players.erase(it.first);
			return;
		}
}

/*
this function will return all the players in the room
input: none
output: players
*/
vector<string> Game::getPlayersInRoom() const
{
	vector<string> players;
	for (auto it = m_players.begin(); it != m_players.end(); ++it)
	{
		players.push_back(it->first.getUsername());
	}
	return players;
}

/*
this function will update avg time for a requested user
input: user, time
output: none
*/
void Game::updateAvgTime(const LoggedUser user, const float time)
{
	for (auto& playersData : m_players) {
		if (playersData.first.getUsername() == user.getUsername())
		{
			int amountOfQuestionsAnswered = playersData.second.correctAnswerCount + playersData.second.wrongAnswerCount;
			playersData.second.averageAnswerTime = ((playersData.second.averageAnswerTime * (amountOfQuestionsAnswered - 1)) + time) / (amountOfQuestionsAnswered);
		}
	}
}

/*
this function will return a requested user game data
input: user
output: playerData
*/
GameData Game::getPlayerGameData(const LoggedUser user) const
{
	GameData playerData;
	for (const auto& playersData : m_players) {
		if (playersData.first.getUsername() == user.getUsername())
			playerData = playersData.second;
	}
	return playerData;
}

/*
this function will receive a user and new game data for that user and update the current game data for that user in the map
input: user, data
output: none
*/
void Game::updateUserData(const LoggedUser user, const GameData data)
{
	for (auto it : m_players)
	{
		if (it.first.getUsername() == user.getUsername())
		{
			it.second = data;
			return;
		}
	}
}

/*
this function will copy all the data from one room to another
input: other
output: updated current room
*/
Game& Game::operator=(const Game& other)
{
	if (this != &other)
	{
		this->m_players = other.m_players;
		this->m_questions = other.m_questions;
	}
	return *this;
}
