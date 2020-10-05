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
}