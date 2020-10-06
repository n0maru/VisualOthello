#include <Siv3D.hpp>
#include "Game.h"
#include "Player.h"
#include "RandomAI.h"

void cvt_char32(char *str, char32_t *str32);

void Main(void)
{
	Scene::SetBackground(Palette::Chocolate);

	double time = 0.0;
	bool finish_flag = false;

	RandomAI player1(std::string("Left Up AI")), player2(std::string("Random AI"));
	Game game(&player1, &player2);

	game.start();
	BoardStatus now_turn_player = game.get_first_player();

	while (System::Update())
	{
		game.print_board(Player1);

		time += Scene::DeltaTime();

		if (time >= 0.5)
		{
			if (!finish_flag)
			{
				ClearPrint();

				game.print_name();

				game.print_name(&player1);
				Print << U" : " << game.count_point(Player1);
				game.print_name(&player2);
				Print << U" : " << game.count_point(Player2);

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
							Print << U"置きました";
						}
						else
						{
							Print << U"置けませんでした";
						}
					}
					else
					{
						Print << U"パスしました";
					}

					now_turn_player = game.get_enemy(now_turn_player);
				}
				else
				{
					game.game_over();
					finish_flag = true;
				}
			}

			time = 0.0;
		}
	}
}

void cvt_char32(char* str, char32_t* str32)
{
	for (int i = 0; i < 8; i++)
	{
		str32[i] = str[i];
	}
}