#include "serverHelper.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

using std::string;

// recieves the type code of the message from socket (3 bytes)
// and returns the code. if no message found in the socket returns 0 (which means the client disconnected)
int Helper::getMessageTypeCode(const SOCKET sc)
{
	char* msgAsArrayOfChars = getPartFromSocket(sc, 3, 0);
	std::string msg(msgAsArrayOfChars);
	delete[] msgAsArrayOfChars;
	if (msg == "")
		return 0;

	int res = std::atoi(msg.c_str());
	return  res;
}

// recieve data from socket according byteSize
// returns the data as string
string Helper::getStringPartFromSocket(const SOCKET sc, const int bytesNum)
{
	char* partFromSocketArr = getPartFromSocket(sc, bytesNum, 0);
	if (partFromSocketArr == nullptr)
		return "";
	std::string str(partFromSocketArr);
	delete[] partFromSocketArr;
	return str;
}

// recieve data from socket according byteSize
// this is private function
std::string Helper::getPartFromSocket(const SOCKET sc, const int bytesNum)
{
	char* partFromSocketArr = getPartFromSocket(sc, bytesNum, 0);
	string str(partFromSocketArr);
	if (partFromSocketArr == nullptr)
		return "";
	delete[] partFromSocketArr;
	return str;
}

// send data to socket
// this is private function
void Helper::sendData(const SOCKET sc, const std::string message)
{
	const char* data = message.c_str();

	if (send(sc, data, message.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
}

/*
this function will convert bytes to int
input: msg
output: the bytes as int
*/
int Helper::convertStringToInt(const char* msg)
{
	return (int)msg[0] * pow(BYTES_SIZE, 3) + (int)msg[1] * pow(BYTES_SIZE, 2) + (int)msg[2] * BYTES_SIZE + (int)msg[3];
}

/*
this function will return the size part from the code massage
input: socket, bytesNum
output: the size
*/
int Helper::getSizePart(const SOCKET sc, const int bytesNum)
{
	char* sizeAsBytes = getPartFromSocket(sc, bytesNum, 0);
	if (sizeAsBytes == nullptr)
		return 0;
	int sizeAsInt = convertStringToInt(sizeAsBytes);
	delete[] sizeAsBytes;
	return sizeAsInt;
}

/*
this function will receive requested amount of bytes to get out from the socket and return them
input: socket, bytesNum, flags
output: data
*/
char* Helper::getPartFromSocket(const SOCKET sc, const int bytesNum, const int flags)
{
	if (bytesNum == 0)
	{
		return nullptr;
	}

	char* data = new char[bytesNum + 1];
	int res = recv(sc, data, bytesNum, flags);
	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(sc);
		throw std::exception(s.c_str());
	}
	data[bytesNum] = '\0';
	return data;
}