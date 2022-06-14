#pragma once
#include <string>
using std::string;
class LoggedUser
{
public:
	LoggedUser(string username);
	~LoggedUser();
	string getUsername() const;
	friend bool operator<(const LoggedUser& first, const LoggedUser& second);
private:
	string m_username;
};