#include "JsonResponsePacketSerializer.h"

string JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& error)
{
	json j;
	return string();
}

string JsonResponsePacketSerializer::serializeResponse(const loginResponse& login)
{
	return string();
}

string JsonResponsePacketSerializer::serializeResponse(const signUpResponse& signup)
{
	return string();
}
