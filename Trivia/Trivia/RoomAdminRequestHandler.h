#pragma once
#include "RoomHandlers.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;
class RoomAdminHandler : public IRequestHandler, public RoomHandler
{
public:
	RoomAdminHandler(const LoggedUser user, RequestHandlerFactory& handlerFactory);
	virtual ~RoomAdminHandler();
	bool isRequestRelevant(const RequestInfo request) const override;
	RequestResult handleRequest(const RequestInfo request) const override;
private:
	RequestHandlerFactory& m_handlerFactory;
	RequestResult getRoomState(const RequestInfo request) const;
	RequestResult closeRoom(const RequestInfo request) const;
	RequestResult startGame(const RequestInfo request) const;
};