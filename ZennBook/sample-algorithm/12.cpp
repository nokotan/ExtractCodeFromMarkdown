# include <Siv3D.hpp>

void Main()
{
	Array<Vec2> points;

	Polygon convexHull;

	while (System::Update())
	{
		if (MouseL.down())
		{
			// 点を追加
			points << Cursor::Pos();

			// 凸包を計算
			convexHull = Geometry2D::ConvexHull(points);
		}

		convexHull.draw(Palette::Skyblue);

		for (const auto& point : points)
		{
			Circle{ point, 5 }.draw(Palette::Seagreen);
		}
	}
}
