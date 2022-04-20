#pragma once
#include "dataBase.h"
#define SCORE_FOR_CORRECT_ANSWER 1000
#define SCORE_FOR_AVG_TIME 250

enum statsSort { USER_NAME, NUM_OF_GAMES, CORRECT_ANSWERS, INCORRECT_ANSWERS, AVG_ANSWER_TIME };

class StatisticsManager
{
public:
	std::vector<std::pair<string, int>> getHighScore() const;
	std::vector<string> getUserStatistics(string username) const;
	
private:
	IDatabase* m_database;
};