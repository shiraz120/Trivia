#include <exception>
#include <string>

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