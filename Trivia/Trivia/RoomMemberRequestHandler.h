#pragma once
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;
class RoomMemberHandler : public IRequestHandler, public RoomHandler
{
public:
	RoomMemberHandler(const LoggedUser user, RequestHandlerFactory& handlerFactory);
	virtual ~RoomMemberHandler();
	bool isRequestRelevant(const RequestInfo request) const override;
	RequestResult handleRequest(const RequestInfo request) const override;
private:
	RequestResult leaveRoom(const RequestInfo request) const;
	RequestResult getRoomState(const RequestInfo request) const;
};