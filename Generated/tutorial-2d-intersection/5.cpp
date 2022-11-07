# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(Palette::White);

	constexpr Rect rect{ 100, 50, 200, 100 };

	constexpr Circle circle{ 200, 400, 100 };

	const Polygon star = Shape2D::Star(200, Vec2{ 550, 300 });

	while (System::Update())
	{
		const Circle c{ Cursor::Pos(), 30 };

		rect.draw(rect.contains(c) ? Palette::Skyblue : Palette::Gray);

		circle.draw(circle.contains(c) ? Palette::Skyblue : Palette::Gray);

		star.draw(star.contains(c) ? Palette::Skyblue : Palette::Gray);

		c.draw(Palette::Seagreen);
	}
}
