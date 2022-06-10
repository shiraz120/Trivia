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
bool LoginRequestHandler::isRequestRelevant(const RequestInfo request) const
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
RequestResult LoginRequestHandler::handleRequest(const RequestInfo request) const
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
RequestResult LoginRequestHandler::login(const RequestInfo request) const
{
	RequestResult result;
	loginResponse data;
	ErrorResponse error;
	loginRequest clientData = JsonRequestPacketDeserializer::deserializeRequest<loginRequest>(request.buffer);
	data.status = STATUS_SUCCESS;
	try {
		m_loginManager.login(clientData.username, clientData.password);
	}
	catch (statusException& e)
	{
		data.status = e.statusRet();
	}
	if (data.status == STATUS_DB_PROBLEM)
		result.response = JsonResponsePacketSerializer::serializeResponse<ErrorResponse>(ErrorResponse{ DATA_BASE_PROBLEM }, ERROR_RESPONSE);
	else
		result.response = JsonResponsePacketSerializer::serializeResponse<loginResponse>(data, LOGIN_RESPONSE);
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
RequestResult LoginRequestHandler::signup(const RequestInfo request) const
{
	RequestResult result;
	signUpResponse data;
	signupRequest clientData = JsonRequestPacketDeserializer::deserializeRequest<signupRequest>(request.buffer);
	data.status = STATUS_SUCCESS;
	try
	{
		m_loginManager.signup(clientData.username, clientData.password, clientData.email);
	}
	catch (statusException& e)
	{
		data.status = e.statusRet();
	}
	if (data.status == STATUS_DB_PROBLEM)
		result.response = JsonResponsePacketSerializer::serializeResponse<ErrorResponse>(ErrorResponse{ DATA_BASE_PROBLEM }, ERROR_RESPONSE);
	else
		result.response = JsonResponsePacketSerializer::serializeResponse<signUpResponse>(data, SIGNUP_RESPONSE);
	result.newHandler = m_handlerFactory.createLoginRequestHandler();
	return result;
}