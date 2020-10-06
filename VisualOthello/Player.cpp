#include "Player.h"

Player::Player(std::string name)
{
	this->player_num = Player1;

	this->name = name;
	std::cout << this->name << std::endl;
}

void Player::set_player_num(BoardStatus player_num)
{
	this->player_num = player_num;
}

bool Player::is_inside(Coordinate coordinate)
{
	if (coordinate.x < 1 || 8 < coordinate.x) return false;
	if (coordinate.y < 1 || 8 < coordinate.y) return false;

	return true;
}

bool Player::can_put(Coordinate coordinate, BoardStatus player, std::vector<std::vector<BoardStatus>> board)
{
	// 盤面の内側か
	if (!Player::is_inside(coordinate)) return false;

	// すでにコマが置かれているか
	if (board[coordinate.y][coordinate.x] != NONE) return false;

	// 挟めるか

	// 上から時計回り
	const int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	const int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
	const BoardStatus enemy = Player::get_enemy(player);

	for (int i = 0; i < 8; i++)
	{
		int delta = 1;
		while (board[(long)coordinate.y + dy[i] * delta][(long)coordinate.x + dx[i] * delta] == enemy)
		{
			++delta;
		}

		if (delta >= 2 && board[(long)coordinate.y + dy[i] * delta][(long)coordinate.x + dx[i] * delta] == player)
		{
			return true;
		}
	}

	return false;
}

BoardStatus Player::get_enemy(BoardStatus player)
{
	if (player == Player1 || player == Player2)
	{
		if (player == Player1) return Player2;
		else return Player1;
	}

	return NONE;
}

std::string Player::get_name()
{
	return this->name;
}