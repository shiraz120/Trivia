#include "StatisticsManager.h"

/*
this function will create a new statisticsManager object
input: db
output: none
*/
StatisticsManager::StatisticsManager(IDatabase* db) : m_database(db)
{
}

/*
this function will remove a StatisticsManager object
input: none
output: none
*/
StatisticsManager::~StatisticsManager()
{
}

/*
this function will return the top 5 most scored players and their score
input: none
output: top 5 most scored players
*/
std::map<string, int> StatisticsManager::getHighScore() const
{
	std::map<string, std::pair<int, float>> users;
	std::vector<std::pair<string, int>> score;
	int counter = 0;
	users = m_database->getUsersStatsForScore();
	for (auto it : users)
	{
		score.push_back(std::pair<string, int>(it.first, it.second.first * SCORE_FOR_CORRECT_ANSWER));
		if(it.second.second > 0)
			score[counter].second += (int)(SCORE_FOR_AVG_TIME / it.second.second);
		counter++;
	}
	std::sort(score.begin(), score.end(), [](auto& left, auto& right) {return left.second < right.second;});
	std::map<string, int> scoreAsMap;
	for (int i = 0; i < AMOUNT_OF_USERS; i++)
	{
		scoreAsMap.emplace(score[i].first, score[i].second);
	}
	return scoreAsMap; 
}

/*
this function will return all the user stats
input: username
output: the user stats
*/
std::vector<string> StatisticsManager::getUserStatistics(string username) const
{
	std::vector<string> stats;
	stats.push_back(username);
	stats.push_back(std::to_string(m_database->getNumOfPlayerGames(username)));
	stats.push_back(std::to_string(m_database->getNumOfCorrectAnswers(username)));
	stats.push_back(std::to_string(m_database->getNumOfTotalAnswers(username)));
	stats.push_back(std::to_string(m_database->getPlayerAverageAnswerTime(username)));
	return stats;
}
