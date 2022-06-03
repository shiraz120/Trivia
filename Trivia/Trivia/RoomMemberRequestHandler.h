#pragma once
#include "RoomHandlers.h"

class RoomMemberHandler : public IRequestHandler, public RoomHandler
{
public:
	RoomMemberHandler(const LoggedUser user, Room& room, RequestHandlerFactory& handlerFactory);
	virtual ~RoomMemberHandler();
	bool isRequestRelevant(const RequestInfo request) override;
	RequestResult handleRequest(const RequestInfo request) override;
private:
	RequestResult leaveRoom(RequestInfo request) const;
	RequestResult getRoomState(RequestInfo request) const;
};