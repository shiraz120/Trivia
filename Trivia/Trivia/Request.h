#pragma once
#include <string>
#include <iostream>
#include "json.hpp"
#define MAX_DATA_LENGTH 4 
#define CODE_LENGTH 1
#define START_OF_DATA MAX_DATA_LENGTH + CODE_LENGTH

enum requestCodes { LOGIN_REQUEST = 'a', SIGNUP_REQUEST = 'b' };

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