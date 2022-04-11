#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "objectsToOrFromJson.h"
#define MAX_BYTE_NUMBER 256

class JsonResponsePacketSerializer
{
public:
	static char* serializeResponse(const ErrorResponse& error);
	static char* serializeResponse(const loginResponse& login);
	static char* serializeResponse(const signUpResponse& signup);

private:
	static string addPaddingZeros(int length);
};