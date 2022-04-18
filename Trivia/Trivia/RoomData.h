#pragma once
#include <string>
#define ACTIVE 1
#define NOT_ACTIVE 0

struct RoomData
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;
};