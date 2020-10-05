#include "D:\VisualOthello\VisualOthello\Game.h"
#include "D:\VisualOthello\VisualOthello\PersonPlayer.h"
#include "D:\VisualOthello\VisualOthello\AIPlayer.h"

// TODO: リプレイ機能の追加

int main(void)
{
	PersonPlayer player1;
	AIPlayer player2;
	Game game(&player1, &player2);

	game.start();
}