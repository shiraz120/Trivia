#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <string>
#include <map>
#include <list>
#include <io.h>
#include <urlmon.h>
#include <vector>
#include "statusException.h"
#include "sqlite3.h"
#include "Question.h"
#include "objectsToOrFromJson.h"
#include <fstream>
#pragma comment(lib, "urlmon.lib")

#define DB_NAME "ClientsTriviaDB.sqlite"
#define URL "https://opentdb.com/api.php?amount=10&type=multiple"
#define FILE_NAME "questions.txt"
#define STATS_USER_NAME "user_name"
#define STATS_AVG_ANSWER_TIME "avarage_answer_time"
#define STATS_INCORRECT_ANSWERS "incorrect_answers"
#define STATS_CORRECT_ANSWER "correct_answers"
#define STATS_AMOUNT_OF_GAMES "amount_of_games"
#define DATA_BASE_PROBLEM "Error: dataBase problem occurred."
#define QUESTION "question"
#define CORRECT_ANSWER "correctAnswer"
#define FIRST_INCORRECT_ANSWER "firstIncorrectAnswer"
#define SECOND_INCORRECT_ANSWER "secondIncorrectAnswer"
#define THIRD_INCORRECT_ANSWER "thirdIncorrectAnswer"

using std::string;

class IDatabase
{
public:
	virtual bool doesUserExist(const string username) const = 0;
	virtual bool doesPasswordMatch(const string username, const string password) const = 0;
	virtual void addNewUser(const string username, const string password, const string email) const = 0;
	virtual std::list<Question> getQuestions(const int amountOfQuestions) const = 0;
	virtual float getPlayerAverageAnswerTime(const string username) const = 0;
	virtual int getNumOfCorrectAnswers(const string username) const = 0;
	virtual int getNumOfTotalAnswers(const string username) const = 0;
	virtual int getNumOfPlayerGames(const string username) const = 0;
	virtual std::map<string, std::pair<int, float>> getUsersStatsForScore() const = 0;
	virtual void updateNumOfPlayersGames(const string username) const = 0;
	virtual void updateNumOfIncorrectAnswers(const string username, unsigned int answers) const = 0;
	virtual void updateNumOfCorrectAnswers(const string username, unsigned int answers) const = 0;
	virtual void updatePlayerAverageAnswerTime(const string username, unsigned int time) const = 0;
};

class SqliteDatabase : public IDatabase
{
public:
	SqliteDatabase();
	~SqliteDatabase();
	bool doesUserExist(const string username) const override;
	bool doesPasswordMatch(const string username, const string password) const override;
	void addNewUser(const string username, const string password, const string email) const override;
	std::list<Question> getQuestions(const int amountOfQuestions) const override;
	int getNumOfPlayerGames(const string username) const  override;
	int getNumOfTotalAnswers(const string username) const override;
	int getNumOfCorrectAnswers(const string username) const override;
	float getPlayerAverageAnswerTime(const string username) const override;
	std::map<string, std::pair<int, float>> getUsersStatsForScore() const override;
	void updateNumOfPlayersGames(const string username) const  override;
	void updateNumOfIncorrectAnswers(const string username, unsigned int answers) const  override;
	void updateNumOfCorrectAnswers(const string username, unsigned int answers) const  override;
	void updatePlayerAverageAnswerTime(const string username, unsigned int time) const override;
	
private:
	sqlite3* _db;
	void initQuestionsTable();
	void createJsonFile() const;
	void sendQuery(const std::string query, int(callBack)(void* data, int argc, char** argv, char** azColName), std::map<string, std::pair<int, float>>* map) const;
	template<class T> void sendQuery(const std::string query, int(callBack)(void* data, int argc, char** argv, char** azColName), std::list<T>* list) const;
	void sendQuery(const std::string query) const;
	void sendQuery(const std::string query, int(callBack)(void* data, int argc, char** argv, char** azColName), float* counter) const;
};

int callBackQuestion(void* data, int argc, char** argv, char** azColName);
int callbackCounter(void* data, int argc, char** argv, char** azColName);
int callbackStats(void* data, int argc, char** argv, char** azColName);
