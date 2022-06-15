#pragma once
#include "dataBase.h"
#include "statusException.h"
#include <map>
#define AMOUNT_OF_USERS 5
#define SCORE_FOR_CORRECT_ANSWER 1000
#define SCORE_FOR_AVG_TIME 250

enum statsSort { USER_NAME, NUM_OF_GAMES, CORRECT_ANSWERS, INCORRECT_ANSWERS, AVG_ANSWER_TIME };

class StatisticsManager
{
public:
	StatisticsManager(IDatabase* db);
	~StatisticsManager();
	std::map<string, int> getHighScore() const;
	std::vector<string> getUserStatistics(const string username) const;
	
private:
	IDatabase* m_database;
};