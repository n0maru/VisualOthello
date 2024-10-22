#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <Siv3D.hpp>
#include "Type.h"
#include "GameVisual.h"

class Replay
{
private:
	std::string filename;
	int now_turn;
	int all_turn;
	BoardStatus first_player;
	std::vector<std::string> players;
	std::vector<std::vector<std::vector<BoardStatus>>> board_data;
	std::vector<GameStatus> game_status;

	bool record(std::string str);
public:
	Replay(std::string filename);
	std::vector<std::vector<BoardStatus>> string_to_board(std::string str);
	std::string board_to_string(std::vector<std::vector<BoardStatus>> board);

	bool set_game_info(std::string player1_name, std::string player2_name, BoardStatus first_player);
	bool record_game_info();
	bool record_board(std::vector<std::vector<BoardStatus>> board, GameStatus game_status);

	bool load_game();
	int count_point(BoardStatus player, std::vector<std::vector<BoardStatus>> board);
	void show_board();
	void update_board();
	void print_first_turn(Font font);
	void print_name(std::string name, Font font, int x, int y);
	void print_name(std::string name, Font font, int x, int y, Color color);
	void print_info(Font font);
	void print_winner(Font font, BoardStatus winner);
	void print_status(Font font);
};