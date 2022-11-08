# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		// 2 次ベジェ曲線
		Bezier2{ Vec2{ 100, 400 }, Vec2{ 100, 250 }, Vec2{ 300, 100 } }
			.draw(4, Palette::Skyblue);

		// 3 次ベジェ曲線
		Bezier3{ Vec2{ 300, 400 }, Vec2{ 400, 400 }, Vec2{ 400, 100 }, Vec2{ 500, 100 }}
			.draw(4, Palette::Orange);
	}
}
