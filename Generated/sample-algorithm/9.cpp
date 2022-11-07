# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 1.0, 0.96, 0.92 });
	const Font font{ 40, Typeface::Heavy };

	const Polygon polygon = Shape2D::Star(240, Scene::Center());
	const LineString contour = polygon.outline();

	LineString contourClosed = contour;
	contourClosed << contour.front();

	// 計算の精度を高めるため LineString を細かくする
	const LineString base = contourClosed.densified(10.0);

	LineString lines;
	double distance = Math::Inf;

	while (System::Update())
	{
		contour.drawClosed(12, ColorF{ 0.7 });

		lines.draw(10, HSV{ 10, 1.0, 0.95 });

		if (MouseL.pressed())
		{
			lines << Cursor::Pos();

			// ハウスドルフ距離を計算
			distance = Geometry2D::HausdorffDistance(base, lines);
		}

		if (MouseR.pressed())
		{
			lines.clear();
			distance = Math::Inf;
		}

		if (IsFinite(distance))
		{
			font(U"{:.2f}"_fmt(distance)).draw(20, 20, ColorF{ 0.25 });
		}
	}
}
