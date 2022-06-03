#pragma once
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"

class RoomAdminHandler;
class LoginRequestHandler;
class MenuRequestHandler;
class RoomMemberHandler;
class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* db);
	~RequestHandlerFactory();
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser user);
	RoomAdminHandler* createRoomAdminRequestHandler();
	RoomMemberHandler* createRoomMemberRequestHandler();
	StatisticsManager& getStatisticsManager();
	RoomManager& getRoomManager();
	LoginManager& getLoginManager();

private:
	LoginManager m_loginManager;
	RoomManager m_roomManager;
	StatisticsManager m_statisticsManager;
	IDatabase* m_database;
};