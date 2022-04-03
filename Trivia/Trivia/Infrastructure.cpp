#include "Infrastructure.h"

/*
this function will call to bindAndListen function and then start to accept users
input: none
output: none
*/
void Communicator::startHandleRequest() 
{
	bindAndListen();
	while (true)
	{
		std::cout << "Waiting for client connection request" << std::endl;
		acceptUsers();
	}
}

/*
this function will open a server socket
input: none
output: none
*/
void Communicator::initServerSocket()
{
	m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

/*
this function will close a server socket
input: none
output: none
*/
void Communicator::closeServerSocket()
{
	try {
		closesocket(m_serverSocket);
	}
	catch (...) {};
}

/*
this function will bind and listen to clients connect requests
input: none
output: none
*/
void Communicator::bindAndListen() 
{
	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(PORT);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = IFACE;
	if (::bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");
	if (::listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
}

/*
this function will handle a new client
input: none
output: none
*/
void Communicator::handleNewClient(SOCKET clientSocket)
{
	LoginRequestHandler newLogin;
	string check;
	m_clients.insert(std::pair<SOCKET, IRequestHandler*>(clientSocket, &newLogin));
	std::cout << "hello" << std::endl;
	std::cin >> check;
	std::cout << check << std::endl;
}

/*
this function will accept a new client and open a new thread to handle the client communication
input: none
output: none
*/
void Communicator::acceptUsers()
{
	SOCKET client_socket = accept(m_serverSocket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);
	thread clientThread(&Communicator::handleNewClient, this, client_socket);
	clientThread.detach();
}

/*
this function will init the server
input: none
output: none
*/
server::server()
{
	m_communicator.initServerSocket();
}

/*
this function will close the server
input: none
output: none
*/
server::~server()
{
	m_communicator.closeServerSocket();
}

/*
this function will run the server by creating a connector thread
input: none
output: none
*/
void server::run()
{
	string userInput;
	thread t_connector(&Communicator::startHandleRequest, m_communicator);
	t_connector.detach();
	while (userInput != "EXIT")
	{
		std::cin >> userInput;
	}
}
