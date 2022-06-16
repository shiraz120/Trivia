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

void to_json(json& jsonCloseRoomResponse, const CloseRoomResponse& closeRoom)
{
	jsonCloseRoomResponse = json{ {"status", closeRoom.status} };
}

void to_json(json& jsonStartGameResponse, const StartGameResponse& createRoom)
{
	jsonStartGameResponse = json{ {"status", createRoom.status} };
}

void to_json(json& jsonGetRoomStateResponse, const GetRoomStateResponse& getRoomState)
{
	jsonGetRoomStateResponse = json{ {"status", getRoomState.status}, {"questionCount", getRoomState.questionCount}, {"players", getRoomState.players},{"hasGameBegun", getRoomState.hasGameBegun}, {"answerTimeout", getRoomState.answerTimeout} };
}

void to_json(json& jsonLeaveRoomResponse, const LeaveRoomResponse& leaveRoom)
{
	jsonLeaveRoomResponse = json{ {"status", leaveRoom.status } };
}

void to_json(json& jsonLeaveGameResponse, const LeaveGameResponse& leaveGame)
{
	jsonLeaveGameResponse = json{ {"status", leaveGame.status } };
}

void to_json(json& jsonGetQuestionResponse, const GetQuestionResponse& getQuestion)
{
	jsonGetQuestionResponse = json{ { "question", getQuestion.question }, {"answers", getQuestion.answers}, {"status", getQuestion.status} };
}

void to_json(json& jsonSubmitAnswerResponse, const SubmitAnswerResponse& submitAnswer)
{
	jsonSubmitAnswerResponse = json{ { "status", submitAnswer.status }, {"correctAnswerId", submitAnswer.correctAnswerId}};
}

void to_json(json& jsonGetGameResultsResponse, const GetGameResultsResponse& getGameResults)
{
	jsonGetGameResultsResponse = json{ { "status", getGameResults.status }, {"results", getGameResults.results} };
}

void to_json(json& jsonLogoutResponse, const LogoutResponse& logout)
{
	jsonLogoutResponse = json{ {"status", logout.status}};
}

void to_json(json& jsonRoom, const RoomData& room)
{
	jsonRoom = json{ {"id", room.id}, {"isActive", room.isActive}, {"maxPlayers", room.maxPlayers}, {"name", room.name}, {"numOfQuestionsInGame", room.numOfQuestionsInGame}, {"timePerQuestion", room.timePerQuestion} };
}

void to_json(json& jsonResults, const PlayerResults& results)
{
	jsonResults = json{ {"wrongAnswerCount", results.wrongAnswerCount} ,{"username", results.username}, {"averageAnswerTime", results.averageAnswerTime}, {"correctAnswerCount",results.correctAnswerCount}};
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

void from_json(const json& jsonGetPlayersInRoomRequest, GetPlayersInRoomRequest& getPlayers)
{
	jsonGetPlayersInRoomRequest.at("roomId").get_to(getPlayers.roomId);
}

void from_json(const json& jsonJoinRoomRequest, JoinRoomRequest& joinRoom)
{
	jsonJoinRoomRequest.at("roomId").get_to(joinRoom.roomId);
}

void from_json(const json& jsonCreateRoomRequest, CreateRoomRequest& createRoom)
{
	jsonCreateRoomRequest.at("answerTimeout").get_to(createRoom.answerTimeout);
	jsonCreateRoomRequest.at("maxUsers").get_to(createRoom.maxUsers);
	jsonCreateRoomRequest.at("questionCount").get_to(createRoom.questionCount);
	jsonCreateRoomRequest.at("roomName").get_to(createRoom.roomName);
}

void from_json(const json& jsonSubmitAnswerRequest, SubmitAnswerRequest& createRoom)
{
	jsonSubmitAnswerRequest.at("answerId").get_to(createRoom.answerId);
}

void from_json(const json& jsonQuestion, Question& questionFromJson)
{
	vector<string> incorrectAnswers;
	string question;
	string correctAnswer;
	string data = jsonQuestion.dump();
	jsonQuestion.at("question").get_to(question);
	jsonQuestion.at("correct_answer").get_to(correctAnswer);
	jsonQuestion.at("incorrect_answers").get_to(incorrectAnswers);
	if(3 - incorrectAnswers.size() > 0)
		incorrectAnswers.insert(incorrectAnswers.end(), (3 - incorrectAnswers.size()), "");
	Question temp(question, correctAnswer, incorrectAnswers[0], incorrectAnswers[1], incorrectAnswers[2]);
	questionFromJson = temp;
}
