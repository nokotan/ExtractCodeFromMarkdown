# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(Palette::White);

	const Vec2 center = Scene::Center();

	const ColorF sunColor{ 0.9, 0.6, 0.3 };

	while (System::Update())
	{
		const double s = (Periodic::Triangle0_1(0.5s) * 20);

		Circle{ center, 120 }.draw(sunColor);

		for (auto i : step(8))
		{
			const double angle = (i * 45_deg);

			const Vec2 pos = OffsetCircular{ center, 160, angle };

			Triangle{ pos, (40 + s), angle }.draw(sunColor);
		}
	}
}
