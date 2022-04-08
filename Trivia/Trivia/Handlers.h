#pragma once
#include <iostream>
#include <string>
#include "Managers.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

using std::string;
struct RequestResult;
class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* db);
	~RequestHandlerFactory();
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler();
	LoginManager& getLoginManager();

private:
	LoginManager m_loginManager;
	IDatabase* m_database;

};

struct RequestInfo
{
	char id;
	string buffer;
	char* receivalTime;
};


class IRequestHandler
{
public:
	virtual ~IRequestHandler() = default;
	virtual bool isRequestRelevant(RequestInfo request) = 0;
	virtual RequestResult handleRequest(RequestInfo request) = 0;
};

class MenuRequestHandler : public IRequestHandler
{
public:
	bool isRequestRelevant(RequestInfo request) override;
	RequestResult handleRequest(RequestInfo request) override;
};

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(LoginManager& loginManager, RequestHandlerFactory& handlerFactory);
	virtual ~LoginRequestHandler();
	bool isRequestRelevant(RequestInfo request) override;
	RequestResult handleRequest(RequestInfo request) override;
private:
	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handlerFactory;
	RequestResult login(RequestInfo request);
	RequestResult signup(RequestInfo request);
};

struct RequestResult
{
	string response;
	IRequestHandler* newHandler;
};