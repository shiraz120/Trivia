#include "serverHelper.h"
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

int Helper::getSizePart(const SOCKET sc, const int bytesNum)
{
	char* sizeAsBytes = getPartFromSocket(sc, bytesNum, 0);
	if (sizeAsBytes == nullptr)
		return 0;
	int sizeAsInt = (int)sizeAsBytes[0] * pow(256, 3) + (int)sizeAsBytes[1] * pow(256, 2) + (int)sizeAsBytes[2] * 256 + (int)sizeAsBytes[3];
	delete[] sizeAsBytes;
	return sizeAsInt;
}

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