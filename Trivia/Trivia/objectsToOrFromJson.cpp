#include "objectsToOrFromJson.h"

void to_json(json& jsonLogin, const loginResponse& login)
{
	jsonLogin = json{ { "status", login.status} };
}

void to_json(json& jsonSignUp, const signUpResponse& signup)
{
	jsonSignUp = json{ { "status", signup.status } };
}

void to_json(json& jsonError, const ErrorResponse& error)
{
	jsonError = json{ { "message", error.message } };
}

void from_json(const json& jsonLogin, loginResponse& login)
{
	jsonLogin.at("status").get_to(login.status);
}

void from_json(const json& jsonSignUp, signUpResponse& signup)
{
	jsonSignUp.at("status").get_to(signup.status);
}

void from_json(const json& jsonError, ErrorResponse& error)
{
	jsonError.at("message").get_to(error.message);
}