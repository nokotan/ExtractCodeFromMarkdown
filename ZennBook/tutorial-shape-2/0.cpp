# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(Palette::White);

	while (System::Update())
	{
		for (auto i : step(10))
		{
			Rect{ 0, (i * 60), 800, 30 }.draw(ColorF{ 0.3, 0.9, 0.6 });
		}
	}
}
