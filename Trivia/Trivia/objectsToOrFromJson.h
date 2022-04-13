#pragma once
#include "Response.h"
#include "Request.h"
// to be able to turn structs to json we created for each struct type a function that does that

/* Response */
void to_json(json& jsonLoginResponse, const loginResponse& login);
void to_json(json& jsonSignUpResponse, const signUpResponse& signup);
void to_json(json& jsonErrorResponse, const ErrorResponse& error);
void to_json(json& jsonLogoutResponse, const LogoutResponse& logout);
void to_json(json& jsonGetRoomsResponse, const GetRoomsResponse& getRooms);
void to_json(json& jsonGetPlayersInRoomResponse, const GetPlayersInRoomResponse& getPlayersInRoom);
void to_json(json& jsonGetHighScoreResponse, const getHighScoreResponse& getHighScore);
void to_json(json& jsonGetPersonalStatsResponse, const getPersonalStatsResponse& getPersonalStats);
void to_json(json& jsonJoinRoomResponse, const JoinRoomResponse& joinRoom);
void to_json(json& jsonCreateRoomResponse, const CreateRoomResponse& createRoom);

/* Request */
void from_json(const json& jsonLoginRequest, loginRequest& login);
void from_json(const json& jsonSignupRequest, signupRequest& signup);

/*RoomData*/
void to_json(json& jsonRoom, const RoomData& room);