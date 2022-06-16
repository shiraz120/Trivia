#pragma once
#include "GameData.h"
#include "LoggedUser.h"
#include "statusException.h"
#include "Response.h"
#include <ctime>
#include <iostream>
#include <vector>
#include <map>
#define NO_MORE_QUESTIONS "GameError: NO MORE QUESTIONS"
#define STATUS_NO_MORE_QUESTIONS 0
#define STATUS_THERE_ARE_STILL_QUESTIONS 1
#define STATUS_GAME_OVER 1
#define STATUS_GAME_NOT_OVER 0
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

	void updateAvgTime(const LoggedUser user, const float time);
	vector<string> getPlayersInRoom() const;
	GameData getPlayerGameData(const LoggedUser user) const;
	void updateUserData(const LoggedUser user, const GameData data);
	
private:
	vector<Question> m_questions;
	map<LoggedUser, GameData> m_players;
};