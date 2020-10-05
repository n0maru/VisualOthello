#pragma once
#include "Type.h"
#include "Player.h"

class PersonPlayer : public Player
{
public:
	PersonPlayer();
	Coordinate calc(std::vector<std::vector<BoardStatus>> board);
};

