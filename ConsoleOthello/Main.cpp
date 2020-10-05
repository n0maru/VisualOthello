#include "..\VisualOthello\Game.h"
#include "..\VisualOthello\PersonPlayer.h"
#include "..\VisualOthello\RandomAI.h"

// TODO: リプレイ機能の追加

int main(void)
{
	PersonPlayer player1;
	RandomAI player2;
	Game game(&player1, &player2);

	game.start();

	BoardStatus now_turn_player = game.get_first_player();

	while (!game.is_finished())
	{
		game.print_board(now_turn_player);

		// TODO: そのターンでnow_turn_playerが置けるかの判別
		// TODO: パスするときの表示
		Coordinate input = game.calc(now_turn_player);

		if (game.set_stone(input, now_turn_player))
		{
			std::cout << "置きました" << std::endl;
		}
		else
		{
			std::cout << "置けませんでした" << std::endl;
		}

		now_turn_player = game.get_enemy(now_turn_player);
	}

	game.game_over();
}