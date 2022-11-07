# include <Siv3D.hpp>

void Main()
{
	constexpr Rect rect{ 150, 200, 400, 100 };

	while (System::Update())
	{
		rect.draw();

		// 時計回りに 45° 回転した長方形
		rect.rotated(45_deg).draw(Palette::Orange);

		// 長方形の左上の座標を回転の軸として時計回りに 60° 回転した長方形
		rect.rotatedAt(rect.pos, 60_deg).draw(Palette::Skyblue);
	}
}
