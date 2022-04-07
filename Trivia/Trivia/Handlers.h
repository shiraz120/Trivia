#pragma once
#include <iostream>
#include <string>
#include "Managers.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

using std::string;
struct RequestResult;
class LoginRequestHandler;

struct RequestInfo
{
	char id;
	string buffer;
	char* receivalTime;
};


class IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo request) = 0;
	virtual RequestResult handleRequest(RequestInfo request) = 0;
};

class LoginRequestHandler : public IRequestHandler
{
public:
	bool isRequestRelevant(RequestInfo request) override;
	RequestResult handleRequest(RequestInfo request) override;
private:
	//LoginManager& m_loginManager;
	//RequestHandlerFactory& m_handlerFactory;
	RequestResult login(RequestInfo);
	RequestResult signup(RequestInfo);
};

struct RequestResult
{
	string response;
	IRequestHandler* newHandler;
};