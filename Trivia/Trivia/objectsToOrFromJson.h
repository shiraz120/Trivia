#pragma once
#include "Response.h"
#include "Request.h"
// to be able to turn structs to json we created for each struct type a function that does that

/* Response */
void to_json(json& jsonLoginResponse, const loginResponse& login);
void to_json(json& jsonSignUpResponse, const signUpResponse& signup);
void to_json(json& jsonErrorResponse, const ErrorResponse& error);
void from_json(const json& jsonLoginResponse, loginResponse& login);
void from_json(const json& jsonSignUpResponse, signUpResponse& signup);
void from_json(const json& jsonErrorResponse, ErrorResponse& error);

/* Request */
void to_json(json& jsonLoginRequest, const loginRequest& login);
void to_json(json& jsonSignupRequest, const signupRequest& signup);
void from_json(const json& jsonLoginRequest, loginRequest& login);
void from_json(const json& jsonSignupRequest, signupRequest& signup);