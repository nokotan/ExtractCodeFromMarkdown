# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(Palette::White);

	constexpr Rect rect{ 100, 50, 200, 100 };

	constexpr Circle circle{ 200, 400, 100 };

	constexpr Triangle triangle{ Vec2{ 500, 100 }, Vec2{ 700, 500 }, Vec2{ 400, 400 } };

	while (System::Update())
	{
		const Line line{ Scene::Center(), Cursor::Pos() };

		// rect と line の交差情報を取得
		if (const auto points = rect.intersectsAt(line))
		{
			rect.draw(Palette::Skyblue);

			// 交差する座標に赤い円を表示
			for (const auto& point : *points)
			{
				Circle{ point, 4 }.draw(Palette::Red);
			}
		}
		else // 交差しない
		{
			rect.draw(Palette::Gray);
		}

		// circle と line の交差情報を取得
		if (const auto points = circle.intersectsAt(line))
		{
			circle.draw(Palette::Skyblue);

			// 交差する座標に赤い円を表示
			for (const auto& point : *points)
			{
				Circle{ point, 4 }.draw(Palette::Red);
			}
		}
		else // 交差しない
		{
			circle.draw(Palette::Gray);
		}

		// triangle と line の交差情報を取得
		if (const auto points = triangle.intersectsAt(line))
		{
			triangle.draw(Palette::Skyblue);

			// 交差する座標に赤い円を表示
			for (const auto& point : *points)
			{
				Circle{ point, 4 }.draw(Palette::Red);
			}
		}
		else // 交差しない
		{
			triangle.draw(Palette::Gray);
		}

		line.draw(2, Palette::Seagreen);
	}
}
