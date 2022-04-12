#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "json.hpp"
#include "RoomData.h"
#define MAX_DATA_LENGTH 4 
#define LOGIN_RESPONSE 'a'
#define SIGNUP_RESPONSE 'b'
#define ERROR_RESPONSE 'c'
#define LOGOUT_RESPONSE 'd'
#define GET_ROOMS_RESPONSE 'e'
#define GET_PLAYERS_IN_ROOM_RESPONSE 'f'
#define GET_HIGH_SCORE_RESPONSE 'g'
#define GET_PERSONAL_STATS_RESPONSE 'h'
#define JOIN_ROOM_RESPONSE 'i'
#define CREATE_ROOM_RESPONSE 'j'

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

struct LogoutResponse
{
	unsigned int status;
};

struct GetRoomsResponse
{
	unsigned int status;
	std::vector<RoomData> rooms;
};

struct GetPlayersInRoomResponse
{
	std::vector <string> players;
};

struct getHighScoreResponse
{
	unsigned int status;
	std::vector<string> statistics;
};

struct getPersonalStatsResponse
{
	unsigned int status;
	std::vector<string> statistics;
};

struct JoinRoomResponse
{
	unsigned int status;
};

struct CreateRoomResponse
{
	unsigned int status;
};