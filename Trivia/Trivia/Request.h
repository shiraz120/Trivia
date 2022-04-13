#pragma once
#include <string>
#include <iostream>
#include "json.hpp"
#define LOGIN_REQUEST '1'
#define SIGNUP_REQUEST '2'
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

struct GetPlayersInRoomRequest
{
	unsigned int roomId;
};

struct JoinRoomRequest
{
	unsigned int roomId;
};

struct CreateRoomRequest
{
	string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
};