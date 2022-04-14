#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <string>
#include <list>
#include <io.h>
#include <urlmon.h>
#include "sqlite3.h"
#include "dataBaseException.h"
#include "convertJsonToHelpers.h"
#include <fstream>
#pragma comment(lib, "urlmon.lib")
#define DB_NAME "ClientsTriviaDB.sqlite"
#define URL "https://opentdb.com/api.php?amount=10"
#define FILE_NAME "questions.txt"

enum STATUS { STATUS_USER_DOESNT_EXIST = 1, STATUS_USER_EXIST, STATUS_PASSWORD_DOESNT_MATCH, STATUS_SUCCESS, STATUS_ALREADY_LOGGED_IN, STATUS_DOESNT_LOGGED_IN, STATUS_DB_PROBLEM};
using std::string;

class IDatabase
{
public:
	virtual bool doesUserExist(const string username) = 0;
	virtual bool doesPasswordMatch(const string username, const string password) = 0;
	virtual void addNewUser(const string username, const string password, const string email) = 0;
	virtual std::list<string> getQuestions(const int i) = 0;
};

class SqliteDatabase : public IDatabase
{
public:
	SqliteDatabase();
	~SqliteDatabase();
	bool doesUserExist(const string username) override;
	bool doesPasswordMatch(const string username, const string password) override;
	void addNewUser(const string username, const string password, const string email) override;
	std::list<string> getQuestions(const int i) override;
private:
	sqlite3* _db;
	void initQuestionsTable();
	void createJsonFile() const;
	template<class T> void sendQuery(const std::string query, int(callBack)(void* data, int argc, char** argv, char** azColName), std::list<T>* list);
	void sendQuery(const std::string query);
	void sendQuery(const std::string query, int(callBack)(void* data, int argc, char** argv, char** azColName), int* counter);
};

int callbackCounter(void* data, int argc, char** argv, char** azColName);
