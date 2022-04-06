#include "JsonResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
int main()
{
	loginRequest e;
	e.password = "hello";
	e.username = "hello";
	json check = e;
	string strOfCheck = "00000" + check.dump();
	loginRequest last = JsonRequestPacketSerializer::deserializeLoginRequest(strOfCheck);

	return 0;
}