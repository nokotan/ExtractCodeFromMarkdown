# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.9, 0.95, 1.0 });

	while (System::Update())
	{
		Rect{ 450, 0, 100, 600 }
			.shearedX(150).draw(HSV{ 40, 0.5, 1.0 });

		Rect{ 550, 0, 400, 600 }
			.shearedX(150).draw(HSV{ 40, 0.8, 1.0 });

		for (auto i : step(5))
		{
			const RoundRect rr{ 50, (60 + i * 100), 350, 80, 40 };
			rr.drawShadow(Vec2{ 4, 4 }, 20, 0)
				.draw();

			Circle{ rr.rect.pos.movedBy(rr.r, rr.r), rr.r }
				.stretched(-5)
				.draw(HSV{ 40, 0.5, 1.0 });
		}
	}
}
