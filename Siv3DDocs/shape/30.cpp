# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		// 始点から終点にかけてグラデーション
		Line{ 100, 100, 500, 150 }
			.draw(6, Palette::Yellow, Palette::Red);

		// 3 つの頂点の色でグラデーション
		Triangle{ 200, 200, 100 }
			.draw(HSV{ 0 }, HSV{ 120 }, HSV{ 240 });

		// 左から右へのグラデーション
		Rect{ 400, 200, 200, 100 }
			.draw(Arg::left = Palette::Skyblue, Arg::right = Palette::Blue);

		// 上から下へのグラデーション
		Rect{ 200, 400, 400, 100 }
			.draw(Arg::top = ColorF{ 1.0, 1.0 }, Arg::bottom = ColorF{ 1.0, 0.0 });
	}
}
