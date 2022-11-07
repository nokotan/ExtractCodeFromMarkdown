# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		// 座標 (100, 100), (400, 300), (100, 300) で構成される三角形を描く
		Triangle{ 100, 100, 400, 300, 100, 300 }.draw();

		// 座標 (300, 100) を重心とする、1 辺が 80px の三角形を描く
		Triangle{ 300, 100, 80 }.draw(Palette::Orange);

		// 時計回りに 15° 回転させて描く
		Triangle{ 400, 100, 80, 15_deg }.draw(Palette::Seagreen);

		// 時計回りに 30° 回転させて描く
		Triangle{ 500, 100, 80, 30_deg }.draw(Palette::Pink);

		// 3 つの頂点座標を Point や Vec2 型で指定
		Triangle{ Cursor::Pos(), Vec2{ 700, 500 }, Vec2{ 100, 500 } }.draw(Palette::Skyblue);
	}
}
