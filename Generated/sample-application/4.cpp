# include <Siv3D.hpp>

void Main()
{
	// 作成した Polygon の配列
	Array<Polygon> polygons;

	// 書き途中の LineString
	LineString points;

	while (System::Update())
	{
		// 左クリックもしくはクリックしたままの移動が発生したら
		if (MouseL.down() ||
			(MouseL.pressed() && (not Cursor::DeltaF().isZero())))
		{
			points << Cursor::PosF();
		}
		else if (MouseL.up())
		{
			points = points.simplified(2.0);

			if (const Polygon polygon = Polygon::CorrectOne(points))
			{
				polygons << polygon;
			}

			points.clear();
		}

		// それぞれの Polygon を描画
		for (auto [i, polygon] : Indexed(polygons))
		{
			polygon.draw(HSV{ (i * 20), 0.4, 1.0 })
				.drawWireframe(1, Palette::Gray)
				.drawFrame(4, HSV{ i * 20 });
		}

		points.draw(4);
	}
}
