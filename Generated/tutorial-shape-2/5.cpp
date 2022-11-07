# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(Palette::White);

	const Vec2 center = Scene::Center();

	while (System::Update())
	{
		const double t = Scene::Time();

		Circle{ center, 120 }
			.drawArc((t * 140_deg), 240_deg, 60, 0, ColorF{ 0.4 });

		Circle{ center, 180 }
			.drawArc((t * 90_deg), 160_deg, 60, 0, ColorF{ 0.6 });

		Circle{ center, 240 }
			.drawArc((t * 50_deg), 120_deg, 60, 0, ColorF{ 0.8 });
	}
}
