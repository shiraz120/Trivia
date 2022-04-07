#include "Managers.h"

/*
this function will signup a user in the data base
input: username, password, email
output: none
*/
void LoginManager::signup(string username, string password, string email)
{
	m_database->addNewUser(username, password, email);
}

/*
this function will login a new user
input: username, password
output: none
*/
void LoginManager::login(string username, string password)
{
	if(m_database->doesUserExist(username))
		if (m_database->doesPasswordMatch(username, password))
		{
			LoggedUser newClient(username);
			m_loggedUsers.push_back(newClient);
		}
}

/*
this function will logout a user
input: username
output: none
*/
void LoginManager::logout(string username)
{
	for(int i = 0; i < m_loggedUsers.size(); i++)
		if(m_loggedUsers[i].getUsername() == username)
			m_loggedUsers.erase(m_loggedUsers.begin() + i);
}

/*
this function will init LoggedUser object
input: username
output: none
*/
LoggedUser::LoggedUser(string username) : m_username(username)
{
}

/*
this function will delete LoggedUser object
input: username
output: none
*/
LoggedUser::~LoggedUser()
{
}

/*
this function returns the username
input: none
output: string - the username
*/
string LoggedUser::getUsername()
{
	return m_username;
}
