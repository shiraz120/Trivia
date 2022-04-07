#include "Handlers.h"

/*
this function will check if a request is valid for login handler
input: request
output: bool - if a request is valid for login handler
*/
bool LoginRequestHandler::isRequestRelevant(RequestInfo request)
{
	if (request.id == LOGIN_REQUEST || request.id == SIGNUP_REQUEST)
		return true;
	return false;
}

/*
this function will receive a request and return the request result that contains the next handler and the response as a string
input: request
output: result
*/
RequestResult LoginRequestHandler::handleRequest(RequestInfo request)
{
	RequestResult result;
	result.newHandler = new LoginRequestHandler(); // replace after adding the next handler
	if (request.id == LOGIN_REQUEST)
	{
		loginResponse data;
		loginRequest clientData = JsonRequestPacketDeserializer::deserializeLoginRequest(request.buffer);
		data.status = 5; // need to add status options, right now '5' doesnt mean any thing, need to add desirializer for checking the user data
		result.response = JsonResponsePacketSerializer::serializeResponse(data);
	}
	else
	{
		signUpResponse data;
		signupRequest clientData = JsonRequestPacketDeserializer::deserializeSignupRequest(request.buffer);
		data.status = 5; // need to add status options, right now '5' doesnt mean any thing
		result.response = JsonResponsePacketSerializer::serializeResponse(data);
	}
	return result;
}
