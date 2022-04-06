#pragma once
#include "objectsToOrFromJson.h"

class JsonRequestPacketSerializer
{
public:
	static loginRequest deserializeLoginRequest(string& buffer);
	static signupRequest deserializeSignupRequest(string& buffer);
};