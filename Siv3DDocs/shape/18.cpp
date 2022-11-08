# include <Siv3D.hpp>

void Main()
{
	// ウィンドウおよびシーンを 1000x600 にリサイズ
	Window::Resize(1000, 600);

	while (System::Update())
	{
		Shape2D::Cross(80, 10, Vec2{ 100, 100 }).draw(Palette::Skyblue);

		Shape2D::Plus(80, 10, Vec2{ 300, 100 }).draw(Palette::Skyblue);

		Shape2D::Pentagon(80, Vec2{ 500, 100 }).draw(Palette::Skyblue);

		Shape2D::Hexagon(80, Vec2{ 700, 100 }).draw(Palette::Skyblue);

		// 30° 回転させる
		Shape2D::Hexagon(80, Vec2{ 900, 100 }, 30_deg).draw(Palette::Skyblue);


		// 正十角形
		Shape2D::Ngon(10, 80, Vec2{ 100, 300 }).draw(Palette::Skyblue);

		Shape2D::Star(80, Vec2{ 300, 300 }).draw(Palette::Skyblue);

		// rOuter は外周の半径、rInner は内周の半径
		Shape2D::NStar(10, 80, 60, Vec2{ 500, 300 }).draw(Palette::Skyblue);

		// headSize は三角形の幅と高さ
		Shape2D::Arrow(Line{ 640, 340, 760, 260 }, 20, Vec2{ 40, 30 }).draw(Palette::Skyblue);

		Shape2D::DoubleHeadedArrow(Line{ 840, 340, 960, 260 }, 20, Vec2{ 40, 30 }).draw(Palette::Skyblue);


		Shape2D::Rhombus(160, 120, Vec2{ 100, 500 }).draw(Palette::Skyblue);

		// 吹き出しの長方形と、三角形の頂点の置を指定。三角形のサイズは pointingRootRatio で決まる
		Shape2D::RectBalloon(RectF{ 220, 420, 160, 120 }, Vec2{ 220, 580 }).draw(Palette::Skyblue);

		// base には階段の最も高い段の底の端の座標を指定。steps は段数、upStairs を false にすると下りの階段に
		Shape2D::Stairs(Vec2{ 560, 560 }, 120, 120, 4).draw(Palette::Skyblue);

		Shape2D::Heart(80, Vec2{ 700, 500 }).draw(Palette::Skyblue);

		// 第 3 引数は角の丸の分割品質
		Shape2D::Squircle(60, Vec2{ 900, 500 }, 64).draw(Palette::Skyblue);
	}
}
