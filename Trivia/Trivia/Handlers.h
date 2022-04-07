#pragma once
#include <iostream>
#include <string>
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

using std::string;
struct RequestResult;

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
};

struct RequestResult
{
	string response;
	IRequestHandler* newHandler;
};