# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	while (System::Update())
	{
		Rect{ 100, 50, 150, 200 }
			.drawShadow(Vec2{ 2, 2 }, 8, 1)
			.draw();

		Rect{ 300, 50, 150, 200 }
			.drawShadow(Vec2{ 4, 4 }, 16, 2)
			.draw();

		Rect{ 500, 50, 150, 200 }
			.drawShadow(Vec2{ 6, 6 }, 24, 3)
			.draw();

		Circle{ 100, 400, 50 }
			.drawShadow(Vec2{ 0, 3 }, 8, 2)
			.draw();

		Circle{ 300, 400, 50 }
			.drawShadow(Vec2{ 3, 0 }, 8, 2)
			.draw();

		Circle{ 500, 400, 50 }
			.drawShadow(Vec2{ 0, -3 }, 8, 2)
			.draw();

		Circle{ 700, 400, 50 }
			.drawShadow(Vec2{ -3, 0 }, 8, 2)
			.draw();
	}
}
