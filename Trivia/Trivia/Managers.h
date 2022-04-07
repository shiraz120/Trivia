#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "dataBase.h"
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
	void signup(string username, string password, string email);
	void login(string username, string password);
	void logout(string username);

private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
};