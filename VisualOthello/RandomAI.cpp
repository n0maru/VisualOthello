#include "RandomAI.h"

RandomAI::RandomAI() : Player::Player()
{
}

Coordinate RandomAI::calc(std::vector<std::vector<BoardStatus>> board)
{
	for (int y = 1; y <= 8; y++)
	{
		for (int x = 1; x <= 8; x++)
		{
			if (Player::can_put(Coordinate{ x, y }, player_num, board))
			{
				return Coordinate{ x, y };
			}
		}
	}

	return Coordinate{ 20, 20 };
}