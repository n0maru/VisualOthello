#include "GameVisual.h"
#include "Player.h"
#include "RandomAI.h"
#include "MaxAI.h"
#include "Replay.h"
#include <Siv3D.hpp>

// TODO: カウントダウンの追加

void Main(void)
{
	Scene::SetBackground(Palette::Chocolate);
	const Font font(20);
	const double LapTime = 0.5;

	double time = 0.0;
	bool finish_flag = false;

	RandomAI player1(std::string("Left Up AI"));
	MaxAI player2(std::string("Max AI"));
	Game game(&player1, &player2);

	Replay replay("D:/replay.txt");
	replay.set_game_info(player1.get_name(), player2.get_name(), game.get_first_player());

	game.start();
	BoardStatus now_turn_player = game.get_first_player();
	BoardStatus winner;

	while (System::Update())
	{
		game.print_first_turn(font);
		game.print_info(font);
		game.print_board(Player1);
		if(finish_flag) game.print_winner(winner, font);
		else game.print_status(game.get_enemy(now_turn_player), font, game.get_game_status());

		time += Scene::DeltaTime();

		if (time >= LapTime)
		{
			if (!finish_flag)
			{
				// 盤面の保存
				replay.record_board(game.get_board());

				ClearPrint();
				if (!game.is_finished())
				{
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
							game.set_status(SET);
						}
						else
						{
							game.set_status(CANNOT_SET);
						}
					}
					else
					{
						game.set_status(PASS);
					}

					now_turn_player = game.get_enemy(now_turn_player);
				}
				else
				{
					winner = game.game_over();
					finish_flag = true;
				}
			}

			time = 0.0;
		}
	}
}