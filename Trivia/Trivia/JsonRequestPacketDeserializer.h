#pragma once
#include "objectsToOrFromJson.h"

class JsonRequestPacketDeserializer
{
public:
	static loginRequest deserializeLoginRequest(string& buffer);
	static signupRequest deserializeSignupRequest(string& buffer);
};