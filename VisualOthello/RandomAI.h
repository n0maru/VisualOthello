#pragma once
#include "Type.h"
#include "Player.h"

class RandomAI : public Player
{
public:
	RandomAI();
	Coordinate calc(std::vector<std::vector<BoardStatus>> board);
};

