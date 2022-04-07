#pragma once
#include <string>
#include <iostream>
#include "json.hpp"
#define LOGIN_REQUEST 'a'
#define SIGNUP_REQUEST 'b'
#define MAX_DATA_LENGTH 4 
#define CODE_LENGTH 1
#define START_OF_DATA MAX_DATA_LENGTH + CODE_LENGTH


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