# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.6 });

	const Polygon starBase1 = Shape2D::Star(100, Scene::Center().movedBy(-160, 0));
	const Polygon starBase2 = Shape2D::Star(100, Scene::Center().movedBy(160, 0));

	Polygon star1 = starBase1;
	Polygon star2 = starBase2;

	double distance = 0;

	while (System::Update())
	{
		if (SimpleGUI::Slider(U"{:.1f}"_fmt(distance), distance, -30.0, 30.0, Vec2{ 20, 20 }))
		{
			// Polygon を太らせ / 細らせる
			star1 = starBase1.calculateRoundBuffer(distance);
			star2 = starBase2.calculateBuffer(distance);
		}

		star1.draw(Palette::Darkblue);
		star2.draw(Palette::Darkblue);

		starBase1.drawFrame(2, Palette::Yellow);
		starBase2.drawFrame(2, Palette::Yellow);
	}
}
