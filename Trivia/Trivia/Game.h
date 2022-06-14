#pragma once
#include "GameData.h"
#include "LoggedUser.h"
#include "statusException.h"
#include <iostream>
#include <vector>
#include <map>
#define NO_MORE_QUESTIONS "GameError: NO MORE QUESTIONS"
#define STATUS_NO_MORE_QUESTIONS 0
#define STATUS_THERE_ARE_STILL_QUESTIONS 1
using std::map;
using std::vector;

class Game
{
public:
	Game();
	Game(const vector<string> players, const vector<Question> questions);
	~Game();
	Question getQuestionForUser(const LoggedUser user);
	void submitAnswer(const LoggedUser user, const string answer);
	void removeUser(const LoggedUser user);
	vector<string> getPlayersInRoom() const;

private:
	vector<Question> m_questions;
	map<LoggedUser, GameData> m_players;
};