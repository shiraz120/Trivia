#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
class RequestHandlerFactory;
class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(LoginManager& loginManager, RequestHandlerFactory& handlerFactory);
	virtual ~LoginRequestHandler();
	bool isRequestRelevant(const RequestInfo request)  const override;
	RequestResult handleRequest(const RequestInfo request) const override;
private:
	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handlerFactory;
	RequestResult login(const RequestInfo request) const;
	RequestResult signup(const RequestInfo request) const;
};