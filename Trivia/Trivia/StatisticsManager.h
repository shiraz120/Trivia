#include "dataBase.h"
#include <vector>
enum statsSort { USER_NAME, NUM_OF_GAMES, CORRECT_ANSWERS, INCORRECT_ANSWERS, AVG_ANSWER_TIME };

class StatisticsManager
{
public:
	std::vector<string> getHighScore() const;
	std::vector<string> getUserStatistics(string username) const;

private:
	IDatabase* m_database;
};