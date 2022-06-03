#include "RequestHandlerFactory.h"
/*
this function will init a RequestHandlerFactory object with a data base
input: db
output: none
*/
RequestHandlerFactory::RequestHandlerFactory(IDatabase* db) : m_database(db), m_loginManager(db), m_statisticsManager(db)
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
MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(const LoggedUser user) 
{
	MenuRequestHandler* newMenuRequestHandler = new MenuRequestHandler(user, *this);
	return newMenuRequestHandler;
}

/*
this function will create a new RoomAdminRequestHandler object
input: user, room
output: new RoomAdminRequestHandler object
*/
RoomAdminHandler* RequestHandlerFactory::createRoomAdminRequestHandler(const LoggedUser user, Room& room)
{
	RoomAdminHandler* newAdminHandler = new RoomAdminHandler(user, room, *this);
	return newAdminHandler;
}

/*
this function will create a new RoomMemberRequestHandler object
input: user, room
output: new RoomMemberRequestHandler object
*/
RoomMemberHandler* RequestHandlerFactory::createRoomMemberRequestHandler(const LoggedUser user, Room& room)
{
	RoomMemberHandler* newMemberHandler = new RoomMemberHandler(user, room, *this);
	return newMemberHandler;
}

/*
this function will return m_statisticsManager
input: none
output: m_statisticsManager
*/
StatisticsManager& RequestHandlerFactory::getStatisticsManager() 
{
	return m_statisticsManager;
}

/*
this function will return m_roomManager
input: none
output: m_roomManager
*/
RoomManager& RequestHandlerFactory::getRoomManager() 
{
	return m_roomManager;
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