#pragma once
#include <string>
#include <iostream>
#include "json.hpp"

using std::string;
using nlohmann::json;

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