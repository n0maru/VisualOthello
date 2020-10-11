#include "Replay.h"

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

	this->all_turn = 0;
	this->now_turn = 0;

	this->board_data.resize(100);
	for (int i = 0; i < 100; i++)
	{
		this->board_data[i].resize(10);
		for (int j = 0; j < 10; j++)
		{
			this->board_data[i][j].resize(10);
		}
	}
}

std::vector<std::vector<BoardStatus>> Replay::string_to_board(std::string str)
{
	int idx = 0;
	std::vector<std::vector<BoardStatus>> board(10, std::vector<BoardStatus>(10, NONE));

	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++, idx++)
		{
			board[y][x] = (BoardStatus) (str[idx] - '0');
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

bool Replay::record_board(std::vector<std::vector<BoardStatus>> board)
{
	std::string str = Replay::board_to_string(board);

	return Replay::record(str);
}

bool Replay::load_game()
{
	std::ifstream fin(this->filename);

	if (!fin.is_open())
	{
		return false;
	}

	std::string line;
	// game info
	// players name
	for (int i = 0; i < 2; i++)
	{
		if (getline(fin, line))
		{
			this->players[i] = line;
		}
		else
		{
			return false;
		}
	}
	// first_player
	if (getline(fin, line))
	{
		this->first_player = (BoardStatus)(line[0] - '0');
	}
	else
	{
		return false;
	}

	this->all_turn = 0;
	while (getline(fin, line))
	{
		this->board_data[this->all_turn] = Replay::string_to_board(line);

		this->all_turn++;
	}

	fin.close();

	return true;
}

int Replay::count_point(BoardStatus player, std::vector<std::vector<BoardStatus>> board)
{
	int count = 0;
	for (int y = 1; y <= 8; y++)
	{
		for (int x = 1; x <= 8; x++)
		{
			if (board[y][x] == player)
			{
				++count;
			}
		}
	}

	return count;
}

void Replay::show_board()
{
	int size = 50;
	int start = 100;
	int r = size / 2;

	// 線を黒色にする
	Rect(start - 1, start - 1, size * 8 + 9).draw(Palette::Black);

	// 盤面の描画
	for (int y = 1; y <= 8; y++)
	{
		for (int x = 1; x <= 8; x++)
		{
			Rect(start + (x - 1) * size + x - 1, start + (y - 1) * size + y - 1, size).draw(Palette::Green);

			// コマを置く
			switch (this->board_data[this->now_turn][y][x])
			{
			case NONE:
				break;
			case Player1:
				Circle(start + (x - 1) * size + x - 1 + r, start + (y - 1) * size + y - 1 + r, r).draw(Palette::White);
				break;
			case Player2:
				Circle(start + (x - 1) * size + x - 1 + r, start + (y - 1) * size + y - 1 + r, r).draw(Palette::Black);
				break;
			default:
				Circle(start + (x - 1) * size + x - 1 + r, start + (y - 1) * size + y - 1 + r, r).draw(Palette::Red);
				break;
			}
		}
	}
}

void Replay::update_board()
{
	if (this->all_turn - this->now_turn >= 2) this->now_turn++;
}