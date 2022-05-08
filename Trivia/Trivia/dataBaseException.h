#pragma once
#include <exception>
#include <string>
enum STATUS { STATUS_USER_DOESNT_EXIST = 1, STATUS_USER_EXIST, STATUS_PASSWORD_DOESNT_MATCH, STATUS_SUCCESS, STATUS_ALREADY_LOGGED_IN, STATUS_DOESNT_LOGGED_IN, STATUS_NO_ROOMS, STATUS_NO_USERS_LOGGED_IN , STATUS_ROOM_DOESNT_EXIST, STATUS_DB_PROBLEM, STATUS_ROOM_IS_FULL };

class dataBaseException : public std::exception
{
public:
	dataBaseException(const std::string& message) : m_message(message) {}
	virtual ~dataBaseException() noexcept = default;
	virtual const char* what() const noexcept { return m_message.c_str(); }
protected:
	std::string m_message;
};

class statusException : public std::exception
{
public:
	statusException(const int status) : m_status(status) {}
	virtual ~statusException() noexcept = default;
	int statusRet() const noexcept { return m_status; }
protected:
	int m_status;
};