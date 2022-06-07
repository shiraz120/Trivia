#include "Communicator.h"

/*
this function will open a server socket and init Communicator object
input: none
output: none
*/
Communicator::Communicator(RequestHandlerFactory& handlerFactory) : m_handlerFactory(handlerFactory)
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
Communicator::~Communicator()
{
	try {
		closesocket(m_serverSocket);
	}
	catch (...) {};
}

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
this function will bind and listen to clients connect requests
input: none
output: none
*/
void Communicator::bindAndListen()
{
	int port = PORT;
	struct sockaddr_in sa = { 0 };
	sa.sin_port = htons(port);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = IFACE;
	if (bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");
	if (listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
}

/*
this function will handle a new client
input: none
output: none
*/
void Communicator::handleNewClient(SOCKET clientSocket)
{
	RequestInfo infoFromClient;
	RequestResult infoToClient;
	ErrorResponse error;
	time_t curentTime;
	std::unique_lock<std::mutex> clientLock(cLock);
	m_clients.insert(std::pair<SOCKET, IRequestHandler*>(clientSocket, m_handlerFactory.createLoginRequestHandler()));
	clientLock.unlock();
	try {
		while (true)
		{
			/* init the request info with the user request */
			infoFromClient.id = *((Helper::getStringPartFromSocket(clientSocket, CODE_LENGTH)).c_str());
			time(&curentTime);
			infoFromClient.receivalTime = ctime(&curentTime);
			infoFromClient.buffer = Helper::getStringPartFromSocket(clientSocket, Helper::getSizePart(clientSocket, MAX_DATA_LENGTH));

			std::cout << "client code: " << infoFromClient.id << std::endl;
			std::cout << "message from client: " + infoFromClient.buffer << std::endl;
			/* if the request is valid for the current handler, create and send the response and replace the handler to a new handler */
			if (!m_clients[clientSocket]->isRequestRelevant(infoFromClient))
			{
				error.message = "Error: request isnt relevant for the current handler.";
				std::cout << "server response: " + error.message << std::endl;
				Helper::sendData(clientSocket, JsonResponsePacketSerializer::serializeResponse<ErrorResponse>(error, ERROR_RESPONSE));
			}
			else
			{
				infoToClient = m_clients[clientSocket]->handleRequest(infoFromClient);
				delete m_clients[clientSocket];
				m_clients[clientSocket] = infoToClient.newHandler;
				Helper::sendData(clientSocket, infoToClient.response);
				std::cout << "server response: " + infoToClient.response << std::endl;
			}
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		std::unique_lock<std::mutex> clientLock(cLock);
		delete m_clients[clientSocket];
		m_clients.erase(clientSocket);
		clientLock.unlock();
		closesocket(clientSocket);
	}
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
	std::cout << "client accepted!" << std::endl;
	thread clientThread(&Communicator::handleNewClient, this, client_socket);
	clientThread.detach();
}
