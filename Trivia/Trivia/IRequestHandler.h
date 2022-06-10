#pragma once
#include <iostream>
#include <string>
#include "LoginManager.h"
#include "StatisticsManager.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestInfo.h"
#include "RequestResult.h"
#include "RoomManager.h"

class IRequestHandler
{
public:
	virtual ~IRequestHandler() = default;
	virtual bool isRequestRelevant(RequestInfo request) const = 0;
	virtual RequestResult handleRequest(RequestInfo request) const = 0;
};