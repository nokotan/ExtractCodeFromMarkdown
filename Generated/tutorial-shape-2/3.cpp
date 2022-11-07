# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(Palette::White);

	while (System::Update())
	{
		const double t = Scene::Time();

		for (auto i : step(12))
		{
			const double angle = (i * 30_deg) + (t * 30_deg);

			const Vec2 pos = OffsetCircular{ Scene::Center(), 160, angle };

			Circle{ pos, 20 }.draw(HSV{ (i * 30) });
		}
	}
}
