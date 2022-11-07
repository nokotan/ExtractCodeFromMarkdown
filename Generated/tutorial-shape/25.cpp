# include <Siv3D.hpp>

void Main()
{
	constexpr Circle circle{ 100, 100, 60 };

	constexpr Rect rect{ 400, 300, 200 };

	while (System::Update())
	{
		circle.draw();

		// (200, 0) の方向に平行移動
		circle.movedBy(200, 0).draw(Palette::Skyblue);

		// (0, 200) の方向に平行移動
		circle.movedBy(0, 200).draw(Palette::Orange);


		rect.drawFrame(2, 2);

		// 上下左右を 10px 縮小
		rect.stretched(-10).drawFrame(2, 2, Palette::Skyblue);

		// 左右を 40px 拡大、上下を 20px 縮小
		rect.stretched(40, -20).drawFrame(2, 2, Palette::Orange);
	}
}
