#include "objectsToOrFromJson.h"

void to_json(json& jsonLoginResponse, const loginResponse& login)
{
	jsonLoginResponse = json{ { "status", login.status} };
}

void to_json(json& jsonSignUpResponse, const signUpResponse& signup)
{
	jsonSignUpResponse = json{ { "status", signup.status } };
}

void to_json(json& jsonErrorResponse, const ErrorResponse& error)
{
	jsonErrorResponse = json{ { "message", error.message } };
}

void to_json(json& jsonGetPersonalStatsResponse, const getPersonalStatsResponse& getPersonalStats)
{
	jsonGetPersonalStatsResponse = json{ {"status", getPersonalStats.status}, {"statistics", getPersonalStats.statistics}};
}

void to_json(json& jsonJoinResponse, const JoinRoomResponse& joinRoom)
{
	jsonJoinResponse = json{ {"status", joinRoom.status} };
}

void to_json(json& jsonCreateRoomResponse, const CreateRoomResponse& createRoom)
{
	jsonCreateRoomResponse = json{ {"status", createRoom.status}};
}

void to_json(json& jsonLogoutResponse, const LogoutResponse& logout)
{
	jsonLogoutResponse = json{ {"status", logout.status}};
}

void to_json(json& jsonRoom, const RoomData& room)
{
	jsonRoom = json{ {"id", room.id}, {"isActive", room.isActive}, {"maxPlayers", room.maxPlayers}, {"name", room.name}, {"numOfQuestionsInGame", room.numOfQuestionsInGame}, {"timePerQuestion", room.timePerQuestion} };
}

void to_json(json& jsonGetRoomsResponse, const GetRoomsResponse& getRooms)
{
	jsonGetRoomsResponse = json{ {"rooms", getRooms.rooms}, {"status", getRooms.status}};
}

void to_json(json& jsonGetPlayersInRoomResponse, const GetPlayersInRoomResponse& getPlayersInRoom)
{
	jsonGetPlayersInRoomResponse = json{ {"players", getPlayersInRoom.players}}; 
}

void to_json(json& jsonGetHighScoreResponse, const getHighScoreResponse& getHighScore)
{
	jsonGetHighScoreResponse = json{ {"statistics", getHighScore.statistics}, {"status", getHighScore.status}};
}

void from_json(const json& jsonLoginRequest, loginRequest& login)
{
	jsonLoginRequest.at("username").get_to(login.username);
	jsonLoginRequest.at("password").get_to(login.password);
}

void from_json(const json& jsonSignupRequest, signupRequest& signup)
{
	jsonSignupRequest.at("username").get_to(signup.username);
	jsonSignupRequest.at("password").get_to(signup.password);
	jsonSignupRequest.at("email").get_to(signup.email);
}