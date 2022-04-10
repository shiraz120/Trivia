#pragma once
#include "objectsToOrFromJson.h"
#include <iomanip>
#include <sstream>
#define MAX_BYTE_NUMBER 255

class JsonResponsePacketSerializer
{
public:
	static char* serializeResponse(const ErrorResponse& error);
	static char* serializeResponse(const loginResponse& login);
	static char* serializeResponse(const signUpResponse& signup);

private:
	static const char* addPaddingZeros(int length);
	static void addFromCharArrToAnother(char* dest, const char* src, const int startIndex, const int sizeOfsrc);
};