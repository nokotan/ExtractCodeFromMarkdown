# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(Palette::White);

	while (System::Update())
	{
		for (auto x : step(8))
		{
			for (auto y : step(6))
			{
				if ((x + y) % 2 == 0)
				{
					Rect{ (x * 100), (y * 100), 100 }
						.draw(ColorF{ 0.3, 0.9, 0.6 });
				}
			}
		}
	}
}
