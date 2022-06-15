#pragma once
#include "RoomHandlers.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;
class RoomMemberHandler : public RoomHandler
{
public:
	RoomMemberHandler(const LoggedUser user, RequestHandlerFactory& handlerFactory);
	virtual ~RoomMemberHandler();
	bool isRequestRelevant(const RequestInfo request) const override;
	RequestResult handleRequest(const RequestInfo request) override;
private:
	RequestHandlerFactory& m_handlerFactory;
	RequestResult leaveRoom(const RequestInfo request) const;
	RequestResult getRoomState(const RequestInfo request) const;
};