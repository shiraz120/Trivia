#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;
class RoomHandler
{
public:
	RoomHandler(const LoggedUser user, Room& room, RequestHandlerFactory& handlerFactory);
	~RoomHandler();
	RequestResult getRoomData(RequestInfo request) const;
protected:
	LoggedUser m_user;
	Room& m_room;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;
};