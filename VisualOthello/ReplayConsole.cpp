#include "ReplayConsole.h"

bool Replay::record(std::string str)
{
	std::ofstream fout(this->filename, std::ios::app);

	if (!fout.is_open())
	{
		return false;
	}

	fout << str << std::endl;

	fout.close();

	return true;
}

Replay::Replay(std::string filename)
{
	this->filename = filename;
	this->first_player = Player1;
	this->players.resize(2);
}

std::vector<std::vector<BoardStatus>> Replay::string_to_board(std::string str)
{
	int idx = 0;
	std::vector<std::vector<BoardStatus>> board(10, std::vector<BoardStatus>(10));

	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++, idx++)
		{
			board[y][x] = (BoardStatus)(str[idx] - '0');
		}
	}

	return board;
}

std::string Replay::board_to_string(std::vector<std::vector<BoardStatus>> board)
{
	std::string str;

	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			str += (char)(board[y][x] + '0');
		}
	}

	return str;
}

bool Replay::set_game_info(std::string player1_name, std::string player2_name, BoardStatus first_player)
{
	this->players[0] = player1_name;
	this->players[1] = player2_name;
	this->first_player = first_player;

	std::ofstream fout(this->filename);
	fout.close();

	return Replay::record_game_info();
}

bool Replay::record_game_info()
{
	std::string str = "";

	for (int i = 0; i < 2; i++)
	{
		str += this->players[i] + '\n';
	}

	str += (char)(this->first_player + '0');

	return Replay::record(str);
}

bool Replay::record_board(std::vector<std::vector<BoardStatus>> board, GameStatus game_status)
{
	std::string str = Replay::board_to_string(board);
	str += ':';
	str += (char)(game_status + '0');

	return Replay::record(str);
}