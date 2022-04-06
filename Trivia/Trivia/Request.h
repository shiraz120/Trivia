#pragma once
#include <string>
#include <iostream>
#include "json.hpp"
#define MAX_DATA_LENGTH 4 

using std::string;
using json = nlohmann::json;

struct loginRequest
{
	string username;
	string password;
};

struct signupRequest
{
	string username;
	string password;
	string email;
};