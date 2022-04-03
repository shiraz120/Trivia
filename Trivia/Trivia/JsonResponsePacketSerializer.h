#pragma once
#include "Response.h"

class JsonResponsePacketSerializer
{
public:
	static string serializeResponse(const ErrorResponse& error);
	static string serializeResponse(const loginResponse& login);
	static string serializeResponse(const signUpResponse& signup);
};