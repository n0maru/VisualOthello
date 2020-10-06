#pragma once
#include "Player.h"
#include "Type.h"
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>

class Game
{
protected:
	std::vector<std::vector<BoardStatus>> board;
	std::vector<Player*> players;
	BoardStatus first_player;
public:
	char player_str[2][8];

	Game(Player* player1, Player* player2);
	void start();
	void print_board(BoardStatus now_turn_player);
	void game_over();
	void print_name();
	void print_name(Player* player);
	bool set_stone(Coordinate coordinate, BoardStatus player);
	bool can_put(Coordinate coordinate, BoardStatus player);
	bool is_inside(Coordinate coordinate);
	bool is_finished();
	BoardStatus get_enemy(BoardStatus player);
	BoardStatus decide_first_player();
	BoardStatus get_first_player();
	Coordinate calc(BoardStatus now_turn_player);
};

