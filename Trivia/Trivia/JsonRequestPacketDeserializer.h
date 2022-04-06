#pragma once
#include "objectsToOrFromJson.h"
class JsonRequestPacketSerializer
{
public:
	loginRequest deserializeLoginRequest(string& buffer);
	signupRequest deserializeSignupRequest(string& buffer);
};