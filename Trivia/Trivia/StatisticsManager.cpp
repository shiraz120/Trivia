#include "StatisticsManager.h"

/*
this function will return the top 5 most scored players and their score
input: none
output: top 5 most scored players
*/
std::vector<string> StatisticsManager::getHighScore() const
{
	return std::vector<string>();
}

/*
this function will return all the user stats
input: username
output: the user stats
*/
std::vector<string> StatisticsManager::getUserStatistics(string username) const
{
	std::vector<string> stats;
	if (!m_database->doesUserExist(username))
		throw statusException(STATUS_USER_DOESNT_EXIST);
	stats.push_back(username);
	stats.push_back(std::to_string(m_database->getNumOfPlayerGames(username)));
	stats.push_back(std::to_string(m_database->getNumOfCorrectAnswers(username)));
	stats.push_back(std::to_string(m_database->getNumOfTotalAnswers(username)));
	stats.push_back(std::to_string(m_database->getPlayerAverageAnswerTime(username)));
	return stats;
}
