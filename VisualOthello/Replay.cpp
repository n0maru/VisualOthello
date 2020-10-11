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

	this->game_status.resize(100);
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

bool Replay::record_board(std::vector<std::vector<BoardStatus>> board, GameStatus game_status)
{
	std::string str = Replay::board_to_string(board);

	str += ':';
	str += (char)(game_status + '0');

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
		//盤面の読み込み
		this->board_data[this->all_turn] = Replay::string_to_board(line.substr(0, 100));
		// Game Status
		this->game_status[this->all_turn] = (GameStatus)(line[101] - '0');

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

void Replay::print_first_turn(Font font)
{
	font(U"先行は ").drawAt(570, 100);
	Color color = (this->first_player == Player1) ? Palette::White : Palette::Black;
	Replay::print_name(this->players[this->first_player], font, 650, 100, color);
}

void Replay::print_name(std::string name, Font font, int x, int y)
{
	Replay::print_name(name, font, x, y, Palette::White);
}

void Replay::print_name(std::string name, Font font, int x, int y, Color color)
{
	char32_t name_char32[100] = { '\n' };

	for (int i = 0; i < name.size(); i++)
	{
		name_char32[i] = name[i];
	}

	font(name_char32).drawAt(x, y, color);
}

void Replay::print_info(Font font)
{
	font(U"White").drawAt(570, 250);
	font(U"Black").drawAt(720, 250, Palette::Black);

	Replay::print_name(this->players[0], font, 570, 280);
	Replay::print_name(this->players[1], font, 720, 280, Palette::Black);

	font(Replay::count_point(Player1, this->board_data[this->now_turn])).drawAt(570, 310);
	font(Replay::count_point(Player2, this->board_data[this->now_turn])).drawAt(720, 310, Palette::Black);
}

void Replay::print_winner(Font font, BoardStatus winner)
{
	if (winner == NONE)
	{
		font(U"Draw ! !").drawAt(570, 400);
	}
	else
	{
		font(U"Winner is ").drawAt(570, 400);
		Replay::print_name(this->players[winner], font, 680, 400);
	}
}

void Replay::print_status(Font font)
{
	int player = (this->now_turn % 2 == 0) ? this->first_player : 1 - this->first_player;
	Replay::print_name(this->players[player], font, 570, 400);

	char32_t status_str[][10] = {
		U"置きました",
		U"置けませんでした",
		U"パスしました"
	};

	font(U" :", status_str[this->game_status[this->now_turn]]).drawAt(700, 400);
}
