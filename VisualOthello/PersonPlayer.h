#pragma once
#include "Type.h"
#include "Player.h"
#include <string>

class PersonPlayer : public Player
{
public:
	PersonPlayer(std::string name);
	Coordinate calc(std::vector<std::vector<BoardStatus>> board);
};

