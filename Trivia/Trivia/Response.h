#pragma once
#include <string>
#include <iostream>
#include "json.hpp"
#define MAX_DATA_LENGTH 4 
enum codes {LOGIN_RESPONSE = 100, SIGNUP_RESPONSE, ERROR_RESPONSE };

using std::string;
using json = nlohmann::json;

struct loginResponse
{
	unsigned int status;
};

struct signUpResponse
{
	unsigned int status;
};

struct ErrorResponse
{
	string message;
};