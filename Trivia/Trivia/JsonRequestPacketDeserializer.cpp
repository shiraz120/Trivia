#include "JsonRequestPacketDeserializer.h"

/*
this function will receive a buffer with a json data in it and return a loginRequest struct
input: buffer
output: loginRequest
*/
loginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(string& buffer)
{
	string jsonString = buffer.substr(START_OF_DATA, buffer.size());
	json jsonFromData = json::parse(jsonString);
	loginRequest loginFromJson = jsonFromData;
	return loginFromJson;
}

/*
this function will receive a buffer with a json data in it and return a signupRequest struct
input: buffer
output: signupRequest
*/
signupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(string& buffer)
{
	string jsonString = buffer.substr(START_OF_DATA, buffer.size());
	json jsonFromData = json::parse(jsonString);
	signupRequest signupFromJson = jsonFromData;
	return signupFromJson;
}
