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
#include "convertJsonToHelpers.h"
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
using std::string;

class IDatabase
{
public:
	virtual bool doesUserExist(const string username) const = 0;
	virtual bool doesPasswordMatch(const string username, const string password) const = 0;
	virtual void addNewUser(const string username, const string password, const string email) const = 0;
	virtual std::list<questionMetaData> getQuestions(const int i) const = 0;
	virtual float getPlayerAverageAnswerTime(const string username) const = 0;
	virtual int getNumOfCorrectAnswers(const string username) const = 0;
	virtual int getNumOfTotalAnswers(const string username) const = 0;
	virtual int getNumOfPlayerGames(const string username) const = 0;
	virtual std::map<string, std::pair<int, float>> getUsersStatsForScore() const = 0;
};

class SqliteDatabase : public IDatabase
{
public:
	SqliteDatabase();
	~SqliteDatabase();
	bool doesUserExist(const string username) const override;
	bool doesPasswordMatch(const string username, const string password) const override;
	void addNewUser(const string username, const string password, const string email) const override;
	std::list<questionMetaData> getQuestions(const int i) const override;
	int getNumOfPlayerGames(const string username) const  override;
	int getNumOfTotalAnswers(const string username) const override;
	int getNumOfCorrectAnswers(const string username) const override;
	float getPlayerAverageAnswerTime(const string username) const override;
	std::map<string, std::pair<int, float>> getUsersStatsForScore() const override;

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
