# include <Siv3D.hpp>

void Main()
{
	Array<Vec2> points =
	{
		Vec2{ 100, 100 }, Vec2{ 200, 200 },
		Vec2{ 300, 300 }, Vec2{ 400, 400 }
	};

	while (System::Update())
	{
		ClearPrint();
		Print << U"count: " << points.size();

		if (points && MouseL.down())
		{
			// 末尾の要素を削除
			points.pop_back();
		}

		for (const auto& point : points)
		{
			Circle{ point, 10 }.draw();
		}
	}
}
