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