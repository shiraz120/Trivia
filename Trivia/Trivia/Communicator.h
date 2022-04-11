#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <map>
#include <thread>
#include "LoginManager.h"
#include <string>
#include <mutex>
#include "serverHelper.h"
#include "LoginRequestHandler.h"

#define PORT 8826;
static const unsigned int IFACE = 0;
using std::thread;
using std::string;
using std::mutex;

class Communicator
{
public:
	Communicator(RequestHandlerFactory& handlerFactory);
	~Communicator();
	void startHandleRequest();

private:
	RequestHandlerFactory& m_handlerFactory;
	void bindAndListen();
	void handleNewClient(SOCKET clientSocket);
	void acceptUsers();
	std::map<SOCKET, IRequestHandler*> m_clients;
	mutex cLock;
	SOCKET m_serverSocket;
};