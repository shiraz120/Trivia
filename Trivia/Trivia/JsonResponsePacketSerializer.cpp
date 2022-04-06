#include "JsonResponsePacketSerializer.h"

/*
this function will return error protocol buffer
input: error
output: error protocol buffer - string
*/
string JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& error)
{
	json jsonError = error;
	string data = jsonError.dump();
	return std::to_string(ERROR_RESPONSE) + addPaddingZeros(data.size()) + data;
}

/*
this function will return login protocol buffer
input: login
output: login protocol buffer - string
*/
string JsonResponsePacketSerializer::serializeResponse(const loginResponse& login)
{
	json jsonLogin = login;
	string data = jsonLogin.dump();
	return std::to_string(LOGIN_RESPONSE) + addPaddingZeros(data.size()) + data;
}

/*
this function will return signup protocol buffer
input: signup
output: signup protocol buffer - string
*/
string JsonResponsePacketSerializer::serializeResponse(const signUpResponse& signup)
{
	json jsonSignup = signup;
	string data = jsonSignup.dump();
	return std::to_string(SIGNUP_RESPONSE) + addPaddingZeros(data.size()) + data;
}

/*
this function will add padding zeros to the length parameter by MAX_DATA_LENGTH defined variable
input: length
output: the length as string with padded zeros
*/
string JsonResponsePacketSerializer::addPaddingZeros(int length)
{
	string paddedLength = std::to_string(length);
	paddedLength.append(MAX_DATA_LENGTH - length, '0');
	return paddedLength;
}
