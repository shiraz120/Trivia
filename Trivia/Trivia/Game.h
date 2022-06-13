#pragma once
#include "GameData.h"
#include "LoggedUser.h"
#include <vector>
#include <map>
using std::map;
using std::vector;

class Game
{
public:
	Question getQuestionForUser(const LoggedUser user) const;
	void submitAnswer(const LoggedUser user, const string answer) const;
	void removeUser(const LoggedUser user) const;

private:
	vector<Question> m_questions;
	map<LoggedUser, GameData> m_players;
};