# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(Palette::White);

	while (System::Update())
	{
		const Vec2 center = Cursor::Pos();

		for (auto i : step(8))
		{
			const double angle = (i * 45_deg);

			const Vec2 from = OffsetCircular{ center, 80, angle };

			const Vec2 to = OffsetCircular{ center, 160, angle };

			Line{ from, to }
				.draw(10, ColorF{ 1.0 }, ColorF{ 0.25 });
		}
	}
}
