#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <map>
#include <thread>
#include "Handlers.h"
#include <string>
#include "serverHelper.h"
#define PORT 8826;

static const unsigned int IFACE = 0;
using std::thread;
using std::string;


class Communicator
{
public:
	void startHandleRequest();
	void initServerSocket();
	void closeServerSocket();
	
private:
	void bindAndListen();
	void handleNewClient(SOCKET clientSocket);
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	void acceptUsers();
};

class server
{
public:
	server();
	~server();
	void run();

private:
	Communicator m_communicator;
};