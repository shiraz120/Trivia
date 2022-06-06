#include "LoginRequestHandler.h"
/*
this function will init a LoginRequestHandler object
input: loginManager, handlerFactory
output: none
*/
LoginRequestHandler::LoginRequestHandler(LoginManager& loginManager, RequestHandlerFactory& handlerFactory) : m_loginManager(loginManager), m_handlerFactory(handlerFactory)
{
}

/*
this function will close a LoginRequestHandler object
input: none
output: none
*/
LoginRequestHandler::~LoginRequestHandler()
{
}

/*
this function will check if a request is valid for login handler
input: request
output: bool - if a request is valid for login handler
*/
bool LoginRequestHandler::isRequestRelevant(RequestInfo request)
{
	if (request.id == LOGIN_REQUEST || request.id == SIGNUP_REQUEST)
		return true;
	return false;
}

/*
this function will receive a request and return the request result that contains the next handler and the response as a string
input: request
output: result
*/
RequestResult LoginRequestHandler::handleRequest(RequestInfo request)
{
	if (request.id == LOGIN_REQUEST)
		return login(request);
	else
		return signup(request);
}

/*
this function will log a new user in and return the result of the request, if it went successfully or not for example
input: request
output: result
*/
RequestResult LoginRequestHandler::login(RequestInfo request)
{
	RequestResult result;
	loginResponse data;
	ErrorResponse error;
	loginRequest clientData = JsonRequestPacketDeserializer::deserializeRequest<loginRequest>(request.buffer);
	data.status = STATUS_SUCCESS;
	try {
		m_loginManager.login(clientData.username, clientData.password);
		result.response = JsonResponsePacketSerializer::serializeResponse<loginResponse>(data, LOGIN_RESPONSE);
	}
	catch (std::exception& e)
	{
		error.message = e.what();
		result.response = JsonResponsePacketSerializer::serializeResponse<ErrorResponse>(error, ERROR_RESPONSE);
		data.status = STATUS_FAILED;
	}
	if (data.status == STATUS_SUCCESS)
		result.newHandler = m_handlerFactory.createMenuRequestHandler(LoggedUser(clientData.username));
	else
		result.newHandler = m_handlerFactory.createLoginRequestHandler();
	return result;
}

/*
this function will sign in a new user in and return the result of the request, if it went successfully or not for example
input: request
output: result
*/
RequestResult LoginRequestHandler::signup(RequestInfo request)
{
	RequestResult result;
	signUpResponse data;
	ErrorResponse error;
	signupRequest clientData = JsonRequestPacketDeserializer::deserializeRequest<signupRequest>(request.buffer);
	data.status = STATUS_SUCCESS;
	try
	{
		m_loginManager.signup(clientData.username, clientData.password, clientData.email);
		result.response = JsonResponsePacketSerializer::serializeResponse<signUpResponse>(data, SIGNUP_RESPONSE);
	}
	catch (std::exception& e)
	{
		error.message = e.what();
		result.response = JsonResponsePacketSerializer::serializeResponse<ErrorResponse>(error, ERROR_RESPONSE);
		data.status = STATUS_FAILED;
	}
	result.newHandler = m_handlerFactory.createLoginRequestHandler();
	return result;
}