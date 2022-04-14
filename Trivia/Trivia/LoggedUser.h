#pragma once
#include <string>
using std::string;
class LoggedUser
{
public:
	LoggedUser(string username);
	~LoggedUser();
	string getUsername() const;
private:
	string m_username;
};