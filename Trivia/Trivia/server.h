#pragma once
#include "Communicator.h"
#include "RequestHandlerFactory.h"
class server
{
public:
	server(IDatabase* dataBase);
	~server();
	void run();

private:
	IDatabase* m_database;
	RequestHandlerFactory m_handlerFactory;
	Communicator m_communicator;
};