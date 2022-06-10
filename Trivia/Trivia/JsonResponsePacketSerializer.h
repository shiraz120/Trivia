#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "objectsToOrFromJson.h"
#define MAX_BYTE_NUMBER 256

class JsonResponsePacketSerializer
{
public:
	template<class T> static string serializeResponse(const T& response, const char code);

private:
	static string addPaddingZeros(int length);
	static string buildSerializeResponse(const string data, const char code);
};

/*
this function will be used to create the response for each reponse struct it receive
input: response, code
output: the response as a string
*/
template<class T> string JsonResponsePacketSerializer::serializeResponse(const T& response, const char code)
{
	json jsonResponse = response;
	string data = jsonResponse.dump();
	return buildSerializeResponse(data, code);
}

