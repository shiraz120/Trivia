#pragma once
#include <iostream>
#include <vector>
#include "LoggedUser.h"
#include "dataBase.h"
#include "statusException.h"
#include <mutex>

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
	std::mutex loggedUsersMutex;
	bool doesUserLoggedIn(string username);
};