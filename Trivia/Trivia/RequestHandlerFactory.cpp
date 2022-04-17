#include "RequestHandlerFactory.h"
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
	LoginRequestHandler* newLoginRequestHandler = new LoginRequestHandler(m_loginManager, *this);
	return newLoginRequestHandler;
}

/*
this function will create a new MenuRequestHandler
input: none
output: newMenuRequestHandler
*/
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