# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.2, 0.3, 0.4 });

	constexpr Rect rect{ 100, 100, 600, 400 };

	double r = 15.0;

	// 点群を生成
	PoissonDisk2D pd{ rect.size, r };

	while (System::Update())
	{
		rect.drawFrame(1, 1, ColorF{ 0.2 });

		for (const auto& point : pd.getPoints())
		{
			Circle{ point, (r / 4) }.movedBy(rect.pos).draw();
		}

		if (SimpleGUI::Slider(r, 5.0, 40.0, Vec2{ 10, 10 }))
		{
			pd = PoissonDisk2D{ rect.size, r };
		}
	}
}
