#pragma once
#include <iostream>
#include <string>
#include <list>
#include <io.h>
#include "sqlite3.h"
#include "dataBaseException.h"
#define DB_NAME "ClientsTriviaDB.sqlite"
using std::string;
class IDatabase
{
public:
	virtual bool doesUserExist(const string username) = 0;
	virtual bool doesPasswordMatch(const string username, const string password) = 0;
	virtual void addNewUser(const string username, const string password, const string email) = 0;
};

class SqliteDatabase : public IDatabase
{
public:
	SqliteDatabase();
	~SqliteDatabase();
	bool doesUserExist(const string username) override;
	bool doesPasswordMatch(const string username, const string password) override;
	void addNewUser(const string username, const string password, const string email) override;
private:
	sqlite3* _db;
	template<class T> void sendQuery(const std::string query, int(callBack)(void* data, int argc, char** argv, char** azColName), std::list<T>* list);
	void sendQuery(const std::string query);
	void sendQuery(const std::string query, int(callBack)(void* data, int argc, char** argv, char** azColName), int* counter);
};

int callbackCounter(void* data, int argc, char** argv, char** azColName);
