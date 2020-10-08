#pragma once
#include "Player.h"
class MaxAI : public Player
{
public:
	MaxAI(std::string name);
	Coordinate calc(std::vector<std::vector<BoardStatus>> board);
};

