# include <Siv3D.hpp>

void Main()
{
	const Spline2D splineA
	{ {
		Vec2{ 100, 60 }, Vec2{ 400, 140 },
		Vec2{ 100, 220 }, Vec2{ 400, 300 },
		Vec2{ 100, 380 }, Vec2{ 400, 460 },
		Vec2{ 100, 540 }
	} };

	// CloseRing::Yes -> 終点から始点も結ぶ
	const Spline2D splineB
	{ {
		Vec2{ 500, 100 }, Vec2{ 700, 200 },
		Vec2{ 600, 500 },
	}, CloseRing::Yes };

	while (System::Update())
	{
		// 太さ 8px で描く
		splineA.draw(8, Palette::Skyblue);

		// 太さ 4px で描く
		splineB.draw(4, Palette::Orange);
	}
}
