#include <Siv3D.hpp>

void Main(void)
{
	Scene::SetBackground(ColorF(1.0, 1.0, 1.0));

	int size = 50;
	int start = 100;
	int r = size / 2;

	while (System::Update())
	{
		// 線を黒色にする
		Rect(start - 1, start - 1, size * 8 + 9).draw(Palette::Black);

		// 盤面の描画
		for (int y = 0; y < 8; y++)
		{
			for (int x = 0; x < 8; x++)
			{
				Rect(start + x * size + x, start + y * size + y, size).draw(Palette::Green);
				Circle(start + x * size + x + r, start + y * size + y + r, r).draw(Palette::White);
			}
		}
	}
}