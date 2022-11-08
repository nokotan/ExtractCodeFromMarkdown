# include <Siv3D.hpp>

void Main()
{
	const Polygon polygon(
		{ Vec2{ 400, 100 }, Vec2{ 600, 300 }, Vec2{ 500, 500 }, Vec2{ 400, 400 }, Vec2{ 300, 500 }, Vec2{ 200, 300 } },
		{ { Vec2{ 450, 250 }, Vec2{ 350, 250 }, Vec2{ 350, 350 }, Vec2{ 450, 350 } } }
	);

	while (System::Update())
	{
		polygon.draw(Palette::Skyblue);
	}
}
