#pragma once
#include <string>
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