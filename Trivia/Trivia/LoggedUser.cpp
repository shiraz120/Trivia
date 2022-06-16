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
string LoggedUser::getUsername() const
{
	return m_username;
}

/*
this function will be used as operator < for a key map usage
input: first, second
output: bool - is smaller
*/
bool operator<(const LoggedUser& first, const LoggedUser& second)
{
	return first.m_username < second.m_username;
}
