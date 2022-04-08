#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "dataBase.h"
#define STATUS_SUCCESS 5
#define STATUS_DB_PROBLEM 10
#define STATUS_USER_EXIST 2
#define STATUS_USER_DOESNT_EXIST 1
#define STATUS_PASSWORD_DOESNT_MATCH 4
#define STATUS_ALREADY_LOGGED_IN 6
#define STATUS_DOESNT_LOGGED_IN 7
using std::string;

class LoggedUser
{
public:
	LoggedUser(string username);
	~LoggedUser();
	string getUsername();
private:
	string m_username;
};

class LoginManager
{
public:
	LoginManager(IDatabase* db);
	~LoginManager();
	void signup(string username, string password, string email);
	void login(string username, string password);
	void logout(string username);

private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
	bool doesUserLoggedIn(string username);
};