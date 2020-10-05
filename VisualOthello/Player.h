#pragma once
#include "Type.h"
#include <vector>
#include <iostream>

class Player
{
protected:
	BoardStatus player_num;
public:
	Player();
	virtual Coordinate calc(std::vector<std::vector<BoardStatus>> board) = 0;
	void set_player_num(BoardStatus player_num);
	bool is_inside(Coordinate coordinate);
	bool can_put(Coordinate coordinate, BoardStatus player, std::vector<std::vector<BoardStatus>> board);
	BoardStatus get_enemy(BoardStatus player);
};