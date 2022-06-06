#pragma once
#include "RoomHandlers.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;
class RoomMemberHandler : public IRequestHandler, public RoomHandler
{
public:
	RoomMemberHandler(const LoggedUser user, RequestHandlerFactory& handlerFactory);
	virtual ~RoomMemberHandler();
	bool isRequestRelevant(const RequestInfo request) override;
	RequestResult handleRequest(const RequestInfo request) override;
private:
	RequestHandlerFactory& m_handlerFactory;
	RequestResult leaveRoom(RequestInfo request) const;
	RequestResult getRoomState(RequestInfo request) const;
};