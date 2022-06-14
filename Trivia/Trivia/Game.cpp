#include "Game.h"

Game::Game()
{
}

Game::Game(const vector<string> players, const vector<Question> questions) : m_questions(questions)
{
	m_questions.push_back(Question(NO_MORE_QUESTIONS, "", "", "", ""));
	for (string player : players)
	{
		m_players.insert({ LoggedUser(player), GameData{m_questions[0], 0, 0, 0}});
	}
}

Game::~Game()
{
}

Question Game::getQuestionForUser(const LoggedUser user)
{
	auto it = m_players.find(user);
	if (it == m_players.end())
		throw statusException(STATUS_USER_NOT_IN_ROOM);
	Question currentQuestion = it->second.currentQuestion;
	if(currentQuestion.getQuestion() == NO_MORE_QUESTIONS)
		throw statusException(STATUS_NO_MORE_QUESTIONS);
	for (int i = 0; i < m_questions.size(); i++ )
	{
		if (m_questions[i].getQuestion() == currentQuestion.getQuestion())
		{
			if ((i + 1) != m_questions.size())
				it->second.currentQuestion = m_questions[i + 1];
		}
	}
	return currentQuestion;
}

void Game::submitAnswer(const LoggedUser user, const string answer)
{
	auto it = m_players.find(user);
	std::pair<int, bool> data;
	if (it == m_players.end())
		throw statusException(STATUS_USER_NOT_IN_ROOM);
	Question currentQuestion = it->second.currentQuestion;
	if (currentQuestion.getCorrentAnswer() == answer)
		it->second.correctAnswerCount += 1;
	else
		it->second.wrongAnswerCount += 1;
}

void Game::removeUser(const LoggedUser user)
{
	if(m_players.find(user) == m_players.end())
		throw statusException(STATUS_USER_NOT_IN_ROOM);
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

