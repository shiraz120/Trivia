#pragma once
#include "IRequestHandler.h"
#include "GameManager.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;
class GameHandler : public IRequestHandler
{
public:
	GameHandler(const LoggedUser user, RequestHandlerFactory& handlerFactory);
	virtual ~GameHandler();
	bool isRequestRelevant(const RequestInfo request) const override;
	RequestResult handleRequest(const RequestInfo request) const override;

private:
	Game m_game;
	LoggedUser m_user;
	GameManager& m_gameManager;
	RequestHandlerFactory& m_handlerFactory;
	RequestResult getQuestion(const RequestInfo request) const;
	RequestResult submitAnswer(const RequestInfo request) const;
	RequestResult getGameResults(const RequestInfo request) const;
	RequestResult leaveGame(const RequestInfo request) const;
};