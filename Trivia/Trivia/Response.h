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

#define CLOSE_ROOM_RESPONSE 'k'
#define START_GAME_RESPONSE 'l'
#define GET_ROOM_STATE_RESPONSE 'm'
#define LEAVE_GAME_RESPONSE 'n'

#define SUBMIT_ANSWER_RSPONSE 'o'
#define LEAVE_GAME_RSPONSE 'p'
#define GET_QUESTION_RSPONSE 'q'
#define GET_GAME_RESULTS_RSPONSE 'r'

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
	std::map<string, int> statistics;
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

struct CloseRoomResponse
{
	unsigned int status;
};

struct StartGameResponse
{
	unsigned int status;
};

struct GetRoomStateResponse
{
	unsigned int status;
	bool hasGameBegun;
	std::vector<string> players;
	unsigned int questionCount;
	unsigned int answerTimeout;
};

struct LeaveRoomResponse
{
	unsigned int status;
};

struct LeaveGameResponse
{
	unsigned int status;
};

struct GetQuestionResponse
{
	unsigned int status;
	string question;
	std::map<unsigned int, std::vector<string>> answers;
};

struct SubmitAnswerResponse
{
	unsigned int status;
	unsigned int correctAnswerId;
};

struct PlayerResults
{
	string username;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
};

struct GetGameResultsResponse
{
	unsigned int status;
	std::vector<PlayerResults> results;
};