#include "GameVisual.h"
#include "Replay.h"
#include <Siv3D.hpp>

// TODO: カウントダウンの追加

void Main(void)
{
	Scene::SetBackground(Palette::Chocolate);
	const Font font(20);
	const double LapTime = 0.5;

	double time = 0.0;

	Replay replay("D:/replay.txt");
	replay.load_game();

	while (System::Update())
	{
		replay.show_board();

		time += Scene::DeltaTime();

		if (time >= LapTime)
		{
			replay.update_board();

			time = 0.0;
		}
	}
}