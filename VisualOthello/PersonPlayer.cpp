#include "PersonPlayer.h"

PersonPlayer::PersonPlayer() : Player::Player()
{
}

Coordinate PersonPlayer::calc(std::vector<std::vector<BoardStatus>> board)
{
	int x, y;
	char c;

	do
	{
		std::cout << std::endl;
		std::cout << "X : ";
		std::cin >> c;
		x = (int)(c - 'a' + 1);
		std::cout << "Y : ";
		std::cin >> y;
	} while (!Player::is_inside(Coordinate{ x, y }));


	return Coordinate{ x , y };
}
