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
	return buildSerializeResponse(data, ERROR_RESPONSE);
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
	return buildSerializeResponse(data, LOGIN_RESPONSE);
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
	return buildSerializeResponse(data, SIGNUP_RESPONSE);
}

/*
this function will add padding nulls to the length parameter by MAX_DATA_LENGTH defined variable
input: length
output: the length as string with padded zeros
*/
string JsonResponsePacketSerializer::addPaddingZeros(int length)
{
	string sizeMsg = "";
	int counter = MAX_DATA_LENGTH - 1;
	std::string padded = "";
	while (length >= MAX_BYTE_NUMBER) // while length is bigger than 255 we add to sizeMsg the char of 255
	{
		sizeMsg += (char)MAX_BYTE_NUMBER;
		length -= MAX_BYTE_NUMBER;
		counter--;
	}
	sizeMsg += (char)length;
	padded = std::string((counter), '\0').append(sizeMsg);
	return padded;
}

/*
this function will create the response string using data and code
input: data, code
output: the full response
*/
string JsonResponsePacketSerializer::buildSerializeResponse(string data, char code)
{
	string size = addPaddingZeros(data.size());
	string codeAsString(CODE_LENGTH, code);
	char* temp = new char[CODE_LENGTH + MAX_DATA_LENGTH + data.size() + 1];
	strcpy(temp, codeAsString.c_str());
	size.copy(temp + CODE_LENGTH, MAX_DATA_LENGTH);
	strncpy(temp + MAX_DATA_LENGTH + CODE_LENGTH, data.c_str(), data.size());
	temp[CODE_LENGTH + MAX_DATA_LENGTH + data.size()] = '\0';
	string response(temp, CODE_LENGTH + MAX_DATA_LENGTH + data.size());
	delete[] temp;
	return response;
}

