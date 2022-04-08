#include "Handlers.h"

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
	RequestResult result; 
	if (request.id == LOGIN_REQUEST)
	{
		result = login(request);
	}
	else
	{
		result = signup(request);
		result.newHandler = m_handlerFactory.createLoginRequestHandler();;
	}
	return result;
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
	loginRequest clientData = JsonRequestPacketDeserializer::deserializeLoginRequest(request.buffer);
	data.status = STATUS_SUCCESS; 
	try {
		m_loginManager.login(clientData.username, clientData.password);
	}
	catch (dataBaseException& dbe)
	{
		data.status = STATUS_DB_PROBLEM;
	}
	catch (statusException& se)
	{
		data.status = se.statusRet();
	}
	if (data.status == STATUS_SUCCESS)
		result.newHandler = m_handlerFactory.createMenuRequestHandler();
	else
		result.newHandler = m_handlerFactory.createLoginRequestHandler();
	result.response = JsonResponsePacketSerializer::serializeResponse(data);
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
	signupRequest clientData = JsonRequestPacketDeserializer::deserializeSignupRequest(request.buffer);
	data.status = STATUS_SUCCESS;
	try
	{
		m_loginManager.signup(clientData.username, clientData.password, clientData.email);
	}
	catch (dataBaseException& dbe)
	{
		data.status = STATUS_DB_PROBLEM;
	}
	catch (statusException& se)
	{
		data.status = se.statusRet();
	}
	result.response = JsonResponsePacketSerializer::serializeResponse(data);
	return result;
}

/*
this function will init a RequestHandlerFactory object with a data base
input: db
output: none
*/
RequestHandlerFactory::RequestHandlerFactory(IDatabase* db) : m_database(db), m_loginManager(db)
{
}

/*
this function will remove a RequestHandlerFactory object
input: none
output: none
*/
RequestHandlerFactory::~RequestHandlerFactory()
{
}

/*
this function will create a new loginRequestHandler
input: none
output: newLoginRequestHandler
*/
LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	LoginRequestHandler* newLoginRequestHandler = new LoginRequestHandler(m_loginManager ,*this);
	return newLoginRequestHandler;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler()
{
	MenuRequestHandler* newMenuRequestHandler = new MenuRequestHandler();
	return newMenuRequestHandler;
}

/*
this function will return the object login manager
input: none
output: m_loginManager
*/
LoginManager& RequestHandlerFactory::getLoginManager()
{
	return m_loginManager;
}

//TODO
bool MenuRequestHandler::isRequestRelevant(RequestInfo request)
{
	return false;
}

//TODO
RequestResult MenuRequestHandler::handleRequest(RequestInfo request)
{
	return RequestResult();
}
