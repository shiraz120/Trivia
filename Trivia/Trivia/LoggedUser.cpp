#include "LoggedUser.h"
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