#include "PersonPlayer.h"

PersonPlayer::PersonPlayer(std::string name) : Player::Player(name)
{
}

Coordinate PersonPlayer::calc(std::vector<std::vector<BoardStatus>> board)
{
	int x, y;
	char c;


	// TODO: クリックによる入力機能
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
