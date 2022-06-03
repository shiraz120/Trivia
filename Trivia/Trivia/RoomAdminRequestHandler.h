#pragma once
#include "RoomHandlers.h"

class RoomAdminHandler : public IRequestHandler, public RoomHandler
{
public:
	RoomAdminHandler(const LoggedUser user, Room& room, RequestHandlerFactory& handlerFactory);
	virtual ~RoomAdminHandler();
	bool isRequestRelevant(const RequestInfo request) override;
	RequestResult handleRequest(const RequestInfo request) override;
private:
	RequestResult getRoomState(RequestInfo request) const;
	RequestResult closeRoom(RequestInfo request) const;
	RequestResult startGame(RequestInfo request) const;
};