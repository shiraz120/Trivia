#include "Handlers.h"

bool LoginRequestHandler::isRequestRelevant(RequestInfo request)
{
	return false;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo request)
{
	return RequestResult();
}
