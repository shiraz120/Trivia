#pragma once
#include "IRequestHandler.h"
class IRequestHandler;
struct RequestResult
{
	string response;
	IRequestHandler* newHandler;
};
