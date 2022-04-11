#include "JsonResponsePacketSerializer.h"


/*
this function will return error protocol buffer
input: error
output: error protocol buffer - string
*/
char* JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& error)
{
	json jsonError = error;
	string data = jsonError.dump();
	string size = addPaddingZeros(data.size());
	string code(CODE_LENGTH, (char)ERROR_RESPONSE);
	char* response = new char[CODE_LENGTH + MAX_DATA_LENGTH + data.size() + 1];
	strncpy(response, code.c_str(), CODE_LENGTH);
	size.copy(response + CODE_LENGTH, MAX_DATA_LENGTH);
	strncpy(response + MAX_DATA_LENGTH + CODE_LENGTH, data.c_str(), data.size());
	response[CODE_LENGTH + MAX_DATA_LENGTH + data.size()] = '\0';
	return response;
}

/*
this function will return login protocol buffer
input: login
output: login protocol buffer - string
*/
char* JsonResponsePacketSerializer::serializeResponse(const loginResponse& login)
{
	json jsonLogin = login;
	string data = jsonLogin.dump();
	string size = addPaddingZeros(data.size());
	string code(CODE_LENGTH, (char)LOGIN_RESPONSE);
	char* response = new char[CODE_LENGTH + MAX_DATA_LENGTH + data.size() + 1];
	strcpy(response, code.c_str());
	size.copy(response + CODE_LENGTH, MAX_DATA_LENGTH);
	strncpy(response + MAX_DATA_LENGTH + CODE_LENGTH, data.c_str(), data.size());
	response[CODE_LENGTH + MAX_DATA_LENGTH + data.size()] = '\0';
	return response;
}

/*
this function will return signup protocol buffer
input: signup
output: signup protocol buffer - string
*/
char* JsonResponsePacketSerializer::serializeResponse(const signUpResponse& signup)
{
	json jsonSignup = signup;
	string data = jsonSignup.dump();
	string size = addPaddingZeros(data.size());
	string code(CODE_LENGTH, (char)SIGNUP_RESPONSE);
	char* response = new char[CODE_LENGTH + MAX_DATA_LENGTH + data.size() + 1];
	strcpy(response, code.c_str());
	size.copy(response + CODE_LENGTH, MAX_DATA_LENGTH);
	strncpy(response + MAX_DATA_LENGTH + CODE_LENGTH, data.c_str(), data.size());
	response[CODE_LENGTH + MAX_DATA_LENGTH + data.size()] = '\0';
	return response;
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

