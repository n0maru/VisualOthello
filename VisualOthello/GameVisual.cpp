#include "Game.h"
#include <Siv3D.hpp>

Game::Game(Player* player1, Player* player2)
{
	// 盤面の初期化
	this->board.resize(10);
	for (int y = 0; y < 10; y++)
	{
		this->board[y].resize(10);
		for (int x = 0; x < 10; x++)
		{
			if (x == 0 || x == 10 || y == 0 || y == 10)
			{
				this->board[y][x] = WALL;
			}
			else
			{
				this->board[y][x] = NONE;
			}
		}
	}

	// 初期コマの配置
	this->board[4][4] = Player1;
	this->board[5][5] = Player1;
	this->board[4][5] = Player2;
	this->board[5][4] = Player2;

	// プレイヤーの初期化
	this->players.resize(2);
	this->players[0] = player1;
	this->players[1] = player2;

	// プレイヤー側の初期化
	this->players[0]->set_player_num(Player1);
	this->players[1]->set_player_num(Player2);

	// first_player
	this->first_player = Player2;

	// player_str
	for (int i = 0; i < 8; i++)
	{
		this->player_str[0][i] = "Player1"[i];
		this->player_str[1][i] = "Player2"[i];
	}

	// game status
	this->game_status = PASS;
}

void Game::start()
{
	Game::decide_first_player();
}

void Game::print_board(BoardStatus now_turn_player)
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
			switch (this->board[y][x])
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

bool Game::set_stone(Coordinate coordinate, BoardStatus player)
{
	if (Game::can_put(coordinate, player))
	{
		this->board[coordinate.y][coordinate.x] = player;
		// 裏返す
		// 上から時計回り
		const int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
		const int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
		const BoardStatus enemy = Game::get_enemy(player);

		for (int i = 0; i < 8; i++)
		{
			bool line_flag = false;
			int delta = 1;

			while (this->board[(long)coordinate.y + dy[i] * delta][(long)coordinate.x + dx[i] * delta] == enemy)
			{
				++delta;
			}

			if (delta >= 2 && this->board[(long)coordinate.y + dy[i] * delta][(long)coordinate.x + dx[i] * delta] == player)
			{
				line_flag = true;
			}

			// 裏返せる方向なら
			if (line_flag)
			{
				delta = 1;
				// 裏返す
				while (this->board[(long)coordinate.y + dy[i] * delta][(long)coordinate.x + dx[i] * delta] == enemy)
				{
					this->board[(long)coordinate.y + dy[i] * delta][(long)coordinate.x + dx[i] * delta] = player;
					++delta;
				}
			}
		}

		return true;
	}

	return false;
}

BoardStatus Game::game_over(Font font)
{
	std::vector<int> point(2, 0);
	for (int y = 1; y <= 8; y++)
	{
		for (int x = 1; x <= 8; x++)
		{
			++point[this->board[y][x]];
		}
	}

	return (point[0] > point[1]) ? Player1 : Player2;
}

void Game::print_info(Font font)
{
	font( U"White").drawAt(570, 250);
	font(U"Black").drawAt(720, 250, Palette::Black);

	Game::print_name(this->players[0], font, 570, 280);
	Game::print_name(this->players[1], font, 720, 280, Palette::Black);

	font(Game::count_point(Player1)).drawAt(570, 310);
	font(Game::count_point(Player2)).drawAt(720, 310, Palette::Black);
}

void Game::set_status(GameStatus status)
{
	this->game_status = status;
}

void Game::print_status(BoardStatus player, Font font, GameStatus status)
{
	Game::print_name(this->players[player], font, 570, 400);

	char32_t status_str[][10] = {
		U"置きました",
		U"置けませんでした",
		U"パスしました"
	};

	font(U" :", status_str[status]).drawAt(700, 400);
}

void Game::print_winner(BoardStatus winner, Font font)
{
	if (winner == NONE)
	{
		font(U"Draw ! !").drawAt(570, 400);
	}
	else
	{
		font(U"Winner is ").drawAt(570, 400);
		Game::print_name(this->players[winner], font, 680, 400);
	}
}

void Game::print_first_turn(Font font)
{
	font(U"先行は ").drawAt(570, 100);
	Game::print_name(this->players[this->first_player], font, 650, 100);
}

void Game::print_name(Player* player, Font font, int x, int y)
{
	std::string name = player->get_name();

	char32_t name_char32[100] = {'\n'};

	for (int i = 0; i < name.size(); i++)
	{
		name_char32[i] = name[i];
	}

	font(name_char32).drawAt(x, y);
}

void Game::print_name(Player* player, Font font, int x, int y, Color color)
{
	std::string name = player->get_name();

	char32_t name_char32[100] = { '\n' };

	for (int i = 0; i < name.size(); i++)
	{
		name_char32[i] = name[i];
	}

	font(name_char32).drawAt(x, y, color);
}

bool Game::can_put(Coordinate coordinate, BoardStatus player)
{
	// 盤面の内側か
	if (!is_inside(coordinate)) return false;

	// すでにコマが置かれているか
	if (this->board[coordinate.y][coordinate.x] != NONE) return false;

	// 挟めるか

	// 上から時計回り
	const int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	const int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
	const BoardStatus enemy = Game::get_enemy(player);

	for (int i = 0; i < 8; i++)
	{
		int delta = 1;
		while (this->board[(long)coordinate.y + dy[i] * delta][(long)coordinate.x + dx[i] * delta] == enemy)
		{
			++delta;
		}

		if (delta >= 2 && this->board[(long)coordinate.y + dy[i] * delta][(long)coordinate.x + dx[i] * delta] == player)
		{
			return true;
		}
	}

	return false;
}

bool Game::is_inside(Coordinate coordinate)
{
	if (coordinate.x < 1 || 8 < coordinate.x) return false;
	if (coordinate.y < 1 || 8 < coordinate.y) return false;

	return true;
}

bool Game::is_finished()
{
	for (int y = 1; y <= 8; y++)
	{
		for (int x = 1; x <= 8; x++)
		{
			if (Game::can_put(Coordinate{ x, y }, Player1) || Game::can_put(Coordinate{ x, y }, Player2)) return false;
		}
	}

	return true;
}

BoardStatus Game::get_enemy(BoardStatus player)
{
	if (player == Player1 || player == Player2)
	{
		if (player == Player1) return Player2;
		else return Player1;
	}

	return NONE;
}

BoardStatus Game::decide_first_player()
{
	srand((unsigned)time(NULL));
	this->first_player = (BoardStatus)(rand() % 2);

	return this->first_player;
}

BoardStatus Game::get_first_player()
{
	return this->first_player;
}

Coordinate Game::calc(BoardStatus now_turn_player)
{
	return this->players[now_turn_player]->calc(this->board);
}

int Game::count_point(BoardStatus player)
{
	int count = 0;
	for (int y = 1; y <= 8; y++)
	{
		for (int x = 1; x <= 8; x++)
		{
			if (this->board[y][x] == player)
			{
				++count;
			}
		}
	}

	return count;
}

GameStatus Game::get_game_status()
{
	return this->game_status;
}
