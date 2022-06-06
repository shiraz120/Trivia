#pragma once
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"

class LoginRequestHandler;
class MenuRequestHandler;
class RoomMemberHandler;
class RoomAdminHandler;
class RequestHandlerFactory
{
public:
	RequestHandlerFactory(IDatabase* db);
	~RequestHandlerFactory();
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(const LoggedUser user);
	RoomAdminHandler* createRoomAdminRequestHandler(const LoggedUser user);
	RoomMemberHandler* createRoomMemberRequestHandler(const LoggedUser user);
	StatisticsManager& getStatisticsManager();
	RoomManager& getRoomManager();
	LoginManager& getLoginManager();

private:
	LoginManager m_loginManager;
	RoomManager m_roomManager;
	StatisticsManager m_statisticsManager;
	IDatabase* m_database;
};