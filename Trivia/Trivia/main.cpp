#include "JsonResponsePacketSerializer.h"
int main()
{
	loginResponse e;
	e.status = 50;
	std::cout << JsonResponsePacketSerializer::serializeResponse(e) << std::endl;

	return 0;
}