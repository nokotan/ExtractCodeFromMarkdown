# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		// 線の幅 3px, 三角の幅 20px, 高さ 20px の単方向矢印を描く
		Line{ 50, 200, 200, 250 }
			.drawArrow(3, Vec2{ 20, 20 }, Palette::Skyblue);

		// 線の幅 10px, 三角の幅 40px, 高さ 80px の単方向矢印を描く
		Line{ 350, 450, 450, 100 }
			.drawArrow(10, Vec2{ 40, 80 }, Palette::Orange);

		// 線の幅 8px, 三角の幅 30px, 高さ 30px の両方向矢印を描く
		Line{ 600, 100, 700, 400 }
			.drawDoubleHeadedArrow(8, Vec2{ 30, 30 }, Palette::Limegreen);
	}
}
