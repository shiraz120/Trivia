#include "server.h"
/*
this function will init the server
input: none
output: none
*/
server::server(IDatabase* dataBase) : m_database(dataBase), m_handlerFactory(m_database), m_communicator(m_handlerFactory)
{
}

/*
this function will close the server
input: none
output: none
*/
server::~server()
{
	delete m_database;
}

/*
this function will run the server by creating a connector thread
input: none
output: none
*/
void server::run()
{
	string userInput;
	thread t_connector(&Communicator::startHandleRequest, &m_communicator);
	t_connector.detach();
	while (userInput != "EXIT")
	{
		std::cin >> userInput;
	}
}