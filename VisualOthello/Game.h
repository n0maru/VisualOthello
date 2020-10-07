#pragma once
#include "Player.h"
#include "Type.h"
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <Siv3D.hpp>

class Game
{
protected:
	std::vector<std::vector<BoardStatus>> board;
	std::vector<Player*> players;
	BoardStatus first_player;
	GameStatus game_status;
public:
	char player_str[2][8];

	Game(Player* player1, Player* player2);
	void start();
	void print_board(BoardStatus now_turn_player);
	void print_name(Player* player, Font font, int x, int y);
	void print_name(Player* player, Font font, int x, int y, Color color);
	void print_info(Font font);
	void set_status(GameStatus status);
	void print_status(BoardStatus player, Font font, GameStatus status);
	void print_winner(BoardStatus winner, Font font);
	void print_first_turn(Font font);
	bool set_stone(Coordinate coordinate, BoardStatus player);
	bool can_put(Coordinate coordinate, BoardStatus player);
	bool is_inside(Coordinate coordinate);
	bool is_finished();
	BoardStatus game_over();
	BoardStatus get_enemy(BoardStatus player);
	BoardStatus decide_first_player();
	BoardStatus get_first_player();
	Coordinate calc(BoardStatus now_turn_player);
	int count_point(BoardStatus player);
	GameStatus get_game_status();
};