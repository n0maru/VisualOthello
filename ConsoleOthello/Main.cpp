#include "..\VisualOthello\GameConsole.h"
#include "..\VisualOthello\PersonPlayer.h"
#include "..\VisualOthello\RandomAI.h"
#include "..\VisualOthello\MaxAI.h"
#include <windows.h>

// TODO: リプレイ機能の追加

int main(void)
{
	RandomAI player1(std::string("Left Top AI"));
	MaxAI player2(std::string("Max AI"));
	Game game(&player1, &player2);

	game.start();

	BoardStatus now_turn_player = game.get_first_player();

	while (!game.is_finished())
	{
		Sleep(0.5 * 1000);
		game.print_board(now_turn_player);

		// そのターンでnow_turn_playerが置けるかの判別
		bool can_put_flag = false;
		for (int y = 1; !can_put_flag && y <= 8; y++)
		{
			for (int x = 1; !can_put_flag && x <= 8; x++)
			{
				if (game.can_put(Coordinate{ x, y }, now_turn_player))
				{
					can_put_flag = true;
				}
			}
		}

		if (can_put_flag)
		{
			Coordinate input = game.calc(now_turn_player);

			if (game.set_stone(input, now_turn_player))
			{
				std::cout << "置きました" << std::endl;
			}
			else
			{
				std::cout << "置けませんでした" << std::endl;
			}
		}
		else
		{
			std::cout << "パスしました" << std::endl;
		}

		now_turn_player = game.get_enemy(now_turn_player);
	}

	game.print_board(now_turn_player);

	game.game_over();
}