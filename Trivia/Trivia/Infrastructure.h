#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <map>
#include <thread>
#include "Handlers.h"
#include <string>
#include <mutex>
#include "serverHelper.h"

#define PORT 8826;
static const unsigned int IFACE = 0;
using std::thread;
using std::string;
using std::mutex;


class Communicator
{
public:
	Communicator();
	~Communicator();
	void startHandleRequest();
	
private:
	void bindAndListen();
	void handleNewClient(SOCKET clientSocket);
	void acceptUsers();
	std::map<SOCKET, IRequestHandler*> m_clients;
	mutex cLock;
	SOCKET m_serverSocket;
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