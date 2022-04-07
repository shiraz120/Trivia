#pragma once
#include "objectsToOrFromJson.h"
#include <iomanip>
#include <sstream>

class JsonResponsePacketSerializer
{
public:
	static string serializeResponse(const ErrorResponse& error);
	static string serializeResponse(const loginResponse& login);
	static string serializeResponse(const signUpResponse& signup);

private:
	static string addPaddingZeros(int length);
};