#pragma once
#include "Type.h"
#include <vector>
#include <iostream>
#include <string>

class Player
{
protected:
	BoardStatus player_num;
	std::string name;
public:
	Player(std::string name);
	virtual Coordinate calc(std::vector<std::vector<BoardStatus>> board) = 0;
	void set_player_num(BoardStatus player_num);
	bool is_inside(Coordinate coordinate);
	bool can_put(Coordinate coordinate, BoardStatus player, std::vector<std::vector<BoardStatus>> board);
	BoardStatus get_enemy(BoardStatus player);
	// TODO: get_name‚Å•Ô‚³‚ê‚é•¶š—ñ‚ğ‚»‚Ì‚Ü‚ÜPrint‚µ‚½‚çƒGƒ‰[“f‚­–â‘è
	std::string get_name();
};