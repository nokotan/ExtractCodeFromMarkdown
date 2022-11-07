# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.96, 0.98, 1.0 });

	Array<Vec2> points;

	while (System::Update())
	{
		if (MouseL.down())
		{
			points << Cursor::Pos();
		}

		if (MouseR.down())
		{
			points.clear();
		}

		const bool isClockwise = Geometry2D::IsClockwise(points);

		ClearPrint();
		Print << isClockwise;

		for (const auto& point : points)
		{
			Circle{ point, 10 }.draw(Palette::Orange);
		}

		if (2 < points.size())
		{
			// 時計回りになるように矢印でつなぐ
			if (isClockwise)
			{
				for (size_t i = 0; i < points.size(); ++i)
				{
					Line{ points[i], points[(i + 1) % points.size()] }
						.stretched(-10)
						.drawArrow(3, Vec2::All(20), ColorF{ 0.25 });
				}
			}
			else
			{
				for (size_t i = 0; i < points.size(); ++i)
				{
					Line{ points[i], points[(i + 1) % points.size()] }
						.reversed()
						.stretched(-10)
						.drawArrow(3, Vec2::All(20), ColorF{ 0.25 });
				}
			}
		}
	}
}
