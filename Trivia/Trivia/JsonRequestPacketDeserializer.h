#pragma once
#include "objectsToOrFromJson.h"

class JsonRequestPacketDeserializer
{
public:
	template<class T> static T deserializeRequest(const string& buffer);
};

/*
this function will receive a buffer and return the struct of the requested request struct
input: buffer
output: the struct request
*/
template<class T> T JsonRequestPacketDeserializer::deserializeRequest(const string& buffer)
{
	json jsonFromData = json::parse(buffer);
	T requestFromJson = jsonFromData;
	return requestFromJson;
}