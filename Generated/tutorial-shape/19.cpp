# include <Siv3D.hpp>

void Main()
{
	const LineString lineA
	{
		Vec2{ 100, 60 }, Vec2{ 400, 140 },
		Vec2{ 100, 220 }, Vec2{ 400, 300 },
		Vec2{ 100, 380 }, Vec2{ 400, 460 },
		Vec2{ 100, 540 }
	};

	const LineString lineB
	{
		Vec2{ 500, 100 }, Vec2{ 700, 200 },
		Vec2{ 600, 500 },
	};

	while (System::Update())
	{
		// 太さ 8px で描く
		lineA.draw(8, Palette::Skyblue);

		// 太さ 4px で描く（終点から始点も結ぶ）
		lineB.drawClosed(4, Palette::Orange);
	}
}
