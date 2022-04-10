#pragma once
#include "IRequestHandler.h"
class IRequestHandler;
struct RequestResult
{
	char* response;
	IRequestHandler* newHandler;
};
