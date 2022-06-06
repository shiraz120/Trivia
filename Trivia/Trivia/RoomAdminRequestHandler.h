#pragma once
#include "RoomHandlers.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;
class RoomAdminHandler : public IRequestHandler, public RoomHandler
{
public:
	RoomAdminHandler(const LoggedUser user, RequestHandlerFactory& handlerFactory);
	virtual ~RoomAdminHandler();
	bool isRequestRelevant(const RequestInfo request) override;
	RequestResult handleRequest(const RequestInfo request) override;
private:
	RequestHandlerFactory& m_handlerFactory;
	RequestResult getRoomState(RequestInfo request) const;
	RequestResult closeRoom(RequestInfo request) const;
	RequestResult startGame(RequestInfo request) const;
};