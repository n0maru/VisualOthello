#include "MaxAI.h"

MaxAI::MaxAI(std::string name) : Player::Player(name)
{
}

Coordinate MaxAI::calc(std::vector<std::vector<BoardStatus>> board)
{
	int max = 0;
	Coordinate max_coordinate;

	for (int y = 1; y <= 8; y++)
	{
		for (int x = 1; x <= 8; x++)
		{
			// 置けるなら
			if (Player::can_put(Coordinate{ x, y }, player_num, board))
			{
				// 座標(x, y)に置いたときに裏返せるコマの数
				int now = Player::can_get_num(Coordinate{ x, y }, this->player_num, board);

				// 現在のmaxよりも多ければ
				if (now > max)
				{
					// maxを更新する
					max = now;
					// maxの座標を更新する
					max_coordinate = Coordinate{ x, y };
				}
			}
		}
	}

	return max_coordinate;
}