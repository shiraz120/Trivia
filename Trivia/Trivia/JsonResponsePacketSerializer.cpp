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
	const char* size = addPaddingZeros(data.size());
	int sizeOfResponse = CODE_LENGTH + MAX_DATA_LENGTH + data.size() + 1;
	char* response = new char[sizeOfResponse];
	response[sizeOfResponse] = '\0';
	addFromCharArrToAnother(response, (std::to_string(ERROR_RESPONSE)).c_str(), 0, CODE_LENGTH);
	addFromCharArrToAnother(response, size, CODE_LENGTH, MAX_DATA_LENGTH);
	addFromCharArrToAnother(response, data.c_str(), MAX_DATA_LENGTH, data.size());
	delete[] size;
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
	const char* size = addPaddingZeros(data.size());
	int sizeOfResponse = CODE_LENGTH + MAX_DATA_LENGTH + data.size() + 1;
	char* response = new char[sizeOfResponse];
	response[sizeOfResponse] = '\0';
	addFromCharArrToAnother(response, (std::to_string(LOGIN_RESPONSE)).c_str(), 0, CODE_LENGTH);
	addFromCharArrToAnother(response, size, CODE_LENGTH, MAX_DATA_LENGTH);
	addFromCharArrToAnother(response, data.c_str(), MAX_DATA_LENGTH, data.size());
	delete[] size;
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
	const char* size = addPaddingZeros(data.size());
	int sizeOfResponse = CODE_LENGTH + MAX_DATA_LENGTH + data.size() + 1;
	char* response = new char[sizeOfResponse];
	response[sizeOfResponse] = '\0';
	addFromCharArrToAnother(response, (std::to_string(SIGNUP_RESPONSE)).c_str(), 0, CODE_LENGTH);
	addFromCharArrToAnother(response, size, CODE_LENGTH, MAX_DATA_LENGTH);
	addFromCharArrToAnother(response, data.c_str(), MAX_DATA_LENGTH, data.size());
	delete[] size;
	return response;
}

/*
this function will add padding nulls to the length parameter by MAX_DATA_LENGTH defined variable
input: length
output: the length as string with padded zeros
*/
const char* JsonResponsePacketSerializer::addPaddingZeros(int length)
{
	char* sizeMsg = new char[MAX_DATA_LENGTH];
	int counter = MAX_DATA_LENGTH  - 1;
	while (length > MAX_BYTE_NUMBER)
	{
		sizeMsg[counter] = (char)MAX_BYTE_NUMBER;
		length -= MAX_BYTE_NUMBER;
		counter--;
	}
	sizeMsg[counter] = (char)length;
	for (int i = 0; i < counter; i++)
		sizeMsg[i] = '\0';
	return sizeMsg;
}

/*
this function will copy all chars from startIndex to sizeOfsrc from src to dest
input: dest, src, startIndex, sizeOfsrc
output: none
*/
void JsonResponsePacketSerializer::addFromCharArrToAnother(char* dest, const char* src, const int startIndex, const int sizeOfsrc)
{
	for (int counter = startIndex; counter < sizeOfsrc; counter++)
	{
		dest[counter] = src[counter];
	}
}
