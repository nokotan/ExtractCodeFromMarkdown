# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(Palette::White);

	while (System::Update())
	{
		for (auto i : step(6))
		{
			Rect{ Arg::center = Scene::Center(), 60, 400 }
				.rotated(i * 30_deg)
				.draw(HSV{ (i * 60), 0.3 });
		}
	}
}
