#pragma once
#include "Response.h"
#include "Request.h"
// to be able to turn structs to json we created for each struct type a function that does that

/* Response */
void to_json(json& jsonLoginResponse, const loginResponse& login);
void to_json(json& jsonSignUpResponse, const signUpResponse& signup);
void to_json(json& jsonErrorResponse, const ErrorResponse& error);

/* Request */
void from_json(const json& jsonLoginRequest, loginRequest& login);
void from_json(const json& jsonSignupRequest, signupRequest& signup);