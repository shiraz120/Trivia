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

Question Game::getQuestionForUser(const LoggedUser user) 
{
	if (m_players[user].currentQuestion.getQuestion() == NO_MORE_QUESTIONS)
		throw statusException(STATUS_NO_MORE_QUESTIONS);
	for (int i = 0; i < m_questions.size(); i++ )
	{
		if (m_questions[i].getQuestion() == m_players[user].currentQuestion.getQuestion())
		{
			if ((i + 1) < m_questions.size())
				m_players[user].currentQuestion = m_questions[i + 1];
		}
	}
	return m_players[user].currentQuestion;
}

void Game::submitAnswer(const LoggedUser user, const string answer)
{
	if (m_players[user].currentQuestion.getCorrentAnswer() == answer)
		m_players[user].correctAnswerCount += 1;
	else
		m_players[user].wrongAnswerCount += 1;
}

void Game::removeUser(const LoggedUser user)
{
	m_players.erase(user);
}

vector<string> Game::getPlayersInRoom() const
{
	vector<string> players;
	for (auto it = m_players.begin(); it != m_players.end(); ++it)
	{
		players.push_back(it->first.getUsername());
	}
	return players;
}

GameData Game::getPlayerGameData(const LoggedUser user) const
{
	GameData playerData;
	for (const auto& playersData : m_players) {
		if (playersData.first.getUsername() == user.getUsername())
			playerData = playersData.second;
	}
	return playerData;
}

bool Game::checkIfGameOver() const
{
	for (auto player : m_players)
	{
		if (player.second.currentQuestion.getQuestion() == NO_MORE_QUESTIONS)
			return false;
	}
	return true;
}

vector<PlayerResults> Game::getAllPlayersData() const
{
	vector<PlayerResults> playersData;
	for (auto it : m_players)
	{
		playersData.push_back(PlayerResults{it.first.getUsername(), it.second.correctAnswerCount, it.second.wrongAnswerCount, it.second.averageAnswerTime});
	}
	return playersData;
}


