#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "objectsToOrFromJson.h"
#define MAX_BYTE_NUMBER 256

class JsonResponsePacketSerializer
{
public:
	static string serializeResponse(const ErrorResponse& error);
	static string serializeResponse(const loginResponse& login);
	static string serializeResponse(const signUpResponse& signup);

private:
	static string addPaddingZeros(int length);
	static string buildSerializeResponse(string data, char code);
};