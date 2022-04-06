#pragma once
#include "Response.h"
#include "Request.h"
// to be able to turn structs to json we created for each struct type a function that does that
void to_json(json& jsonLogin, const loginResponse& login);
void to_json(json& jsonSignUp, const signUpResponse& signup);
void to_json(json& jsonError, const ErrorResponse& error);
void from_json(const json& jsonLogin, loginResponse& login);
void from_json(const json& jsonSignUp, signUpResponse& signup);
void from_json(const json& jsonError, ErrorResponse& error);