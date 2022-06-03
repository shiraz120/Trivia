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
void to_json(json& jsonCloseRoomResponse, const CloseRoomResponse& closeRoom);
void to_json(json& jsonStartGameResponse, const StartGameResponse& createRoom);
void to_json(json& jsonGetRoomStateResponse, const GetRoomStateResponse& getRoomState);
void to_json(json& jsonLeaveRoomResponse, const LeaveRoomResponse& leaveRoom);

/* Request */
void from_json(const json& jsonLoginRequest, loginRequest& login);
void from_json(const json& jsonSignupRequest, signupRequest& signup);
void from_json(const json& jsonGetPlayersInRoomRequest, GetPlayersInRoomRequest& getPlayers);
void from_json(const json& jsonJoinRoomRequest, JoinRoomRequest& joinRoom);
void from_json(const json& jsonCreateRoomRequest, CreateRoomRequest& createRoom);

/*RoomData*/
void to_json(json& jsonRoom, const RoomData& room);