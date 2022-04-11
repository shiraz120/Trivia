#pragma once
#include <string>
#include <iostream>
#include "json.hpp"
#define MAX_DATA_LENGTH 4 
#define LOGIN_RESPONSE '1'
#define SIGNUP_RESPONSE '2'
#define ERROR_RESPONSE '3'

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