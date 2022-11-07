# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(Palette::White);

	while (System::Update())
	{
		for (auto x : step(9))
		{
			for (auto y : step(7))
			{
				Circle{ x * 100, y * 100, 20 }
					.draw(ColorF{ 0.3, 0.6, 0.9 });
			}
		}
	}
}
