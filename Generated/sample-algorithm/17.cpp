# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);

	const Font font{ 20, Typeface::Bold };

	Array<Vec2> points;
	Array<Polygon> solvedPolygons;

	while (System::Update())
	{
		if (MouseL.down())
		{
			points << Cursor::Pos();

			// 頂点列から適切な Polygon を作成
			solvedPolygons = Polygon::Correct(points, {});
		}
		else if (MouseR.down())
		{
			points.clear();
			solvedPolygons.clear();
		}

		for (auto [i, point] : Indexed(points))
		{
			Circle{ point, 5 }.draw();
			Line{ points[i], points[(i + 1) % points.size()] }
			.drawArrow(2, Vec2{ 20, 20 }, Palette::Orange);
		}

		font(points).draw(Rect{ 20, 20, 600, 720 });

		{
			const Transformer2D transformer{ Mat3x2::Translate(640, 0) };

			font(solvedPolygons).draw(Rect{ 20, 20, 600, 720 });

			for (auto [i, solvedPolygon] : Indexed(solvedPolygons))
			{
				const HSV color{ (i * 40.0), 0.7, 1.0 };
				solvedPolygon.draw(color);

				const auto& outer = solvedPolygon.outer();

				for (auto [k, point] : Indexed(outer))
				{
					const Vec2 begin = outer[k];
					const Vec2 end = outer[(k + 1) % outer.size()];
					const Vec2 v = (end - begin).normalized();
					const Vec2 c = (begin + end) / 2;
					const Vec2 oc = c + v.rotated(-90_deg) * 10;
					Line{ oc - v * 20, oc + v * 20 }
						.drawArrow(2, Vec2{ 10, 10 }, color);
				}
			}
		}
	}
}
