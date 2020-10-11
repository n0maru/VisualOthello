#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "Type.h"
#include "GameConsole.h"

class Replay
{
private:
	std::string filename;
	BoardStatus first_player;
	std::vector<std::string> players;

	bool record(std::string str);
public:
	Replay(std::string filename);
	std::vector<std::vector<BoardStatus>> string_to_board(std::string str);
	std::string board_to_string(std::vector<std::vector<BoardStatus>> board);

	bool set_game_info(std::string player1_name, std::string player2_name, BoardStatus first_player);
	bool record_game_info();
	bool record_board(std::vector<std::vector<BoardStatus>> board, GameStatus game_status);
};