#pragma once
#include "objectsToOrFromJson.h"

class JsonResponsePacketSerializer
{
public:
	static string serializeResponse(const ErrorResponse& error);
	static string serializeResponse(const loginResponse& login);
	static string serializeResponse(const signUpResponse& signup);

private:
	static string addPaddingZeros(int length);
};