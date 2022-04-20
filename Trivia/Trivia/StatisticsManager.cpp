#include "StatisticsManager.h"
#include "dataBaseException.h"

/*
this function will return the top 5 most scored players and their score
input: none
output: top 5 most scored players
*/
std::vector<std::pair<string, int>> StatisticsManager::getHighScore() const
{
	std::map<string, std::pair<int, float>> users;
	std::vector<std::pair<string, int>> score;
	int counter = 0;
	users = m_database->getUsersStatsForScore();
	if (users.size() == 0)
		throw statusException(STATUS_NO_USERS_LOGGED_IN);
	for (auto it : users)
	{
		score.push_back(std::pair<string, int>(it.first, it.second.first * SCORE_FOR_CORRECT_ANSWER));
		score[counter].second += (int)(SCORE_FOR_AVG_TIME / it.second.second);
		counter++;
	}
	std::sort(score.begin(), score.end(), [](auto& left, auto& right) {return left.second < right.second;});
	return score;
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
