#include "LoginManager.h"

/*
this function will init a login manager object with a data base
input: db
output: none
*/
LoginManager::LoginManager(IDatabase* db) : m_database(db)
{
}

/*
this function will delete a LoginManager object
input: none
output: none
*/
LoginManager::~LoginManager()
{
}

/*
this function will signup a user in the data base
input: username, password, email
output: none
*/
void LoginManager::signup(string username, string password, string email)
{
	if (!m_database->doesUserExist(username))
		m_database->addNewUser(username, password, email);
	else
		throw statusException(STATUS_USER_EXIST);
}

/*
this function will login a new user
input: username, password
output: none
*/
void LoginManager::login(string username, string password)
{
	if (doesUserLoggedIn(username))
		throw statusException(STATUS_ALREADY_LOGGED_IN);
	else if (m_database->doesUserExist(username))
		if (m_database->doesPasswordMatch(username, password))
		{
			LoggedUser newClient(username);
			m_loggedUsers.push_back(newClient);
		}
		else
			throw statusException(STATUS_PASSWORD_DOESNT_MATCH);
	else
		throw statusException(STATUS_USER_DOESNT_EXIST);
}

/*
this function will logout a user
input: username
output: none
*/
void LoginManager::logout(string username)
{
	if (!doesUserLoggedIn(username))
		throw statusException(STATUS_DOESNT_LOGGED_IN);
	for (int i = 0; i < m_loggedUsers.size(); i++)
		if (m_loggedUsers[i].getUsername() == username)
			m_loggedUsers.erase(m_loggedUsers.begin() + i);
}

/*
this function will check if a user already logged in
input: username
output: bool - if logged in or not
*/
bool LoginManager::doesUserLoggedIn(string username)
{
	for (int i = 0; i < m_loggedUsers.size(); i++)
		if (m_loggedUsers[i].getUsername() == username)
			return true;
	return false;
}