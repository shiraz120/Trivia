#pragma once
#include <string>
#include <iostream>
#include "json.hpp"
/*LOGIN HANLDER*/
#define LOGIN_REQUEST '1'
#define SIGNUP_REQUEST '2'

/*MENU HANDLER*/
#define CREATE_ROOM_REQUEST '3'
#define GET_ROOMS_REQUEST '4'
#define SIGN_OUT_REQUEST '5'
#define GET_PLAYERS_IN_ROOM_REQUEST '6'
#define GET_PERSONAL_STATS_REQUEST '7'
#define GET_HIGH_SCORE_REQUEST '8'
#define JOIN_ROOM_REQUEST '9'

/*ROOMS_HANLDERS*/
#define CLOSE_ROOM_REQUEST 'A'
#define GET_ROOM_STATE_REQUEST 'B'
#define START_GAME_REQUEST 'C'
#define LEAVE_ROOM_REQUEST 'D'

/*GAME_HANDLER*/
#define SUBMIT_ANSWER_REQUEST 'E'
#define LEAVE_GAME_REQUEST 'F'
#define GET_QUESTION_REQUEST 'G'
#define GET_GAME_RESULTS_REQUEST 'H'

#define GET_RANDOM_MASSAGE_REQUEST 'Z'

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

struct SubmitAnswerRequest
{
	unsigned int answerId;
};