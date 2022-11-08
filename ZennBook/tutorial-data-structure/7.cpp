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
		// イテレータですべての要素にアクセスする
		for (auto it = points.begin(); it != points.end();)
		{
			// 円がクリックされたらその地点を表す要素を削除
			if (Circle(*it, 30).leftClicked())
			{
				// 現在のイテレータが指す要素を削除し、イテレータを進める
				it = points.erase(it);
			}
			else
			{
				// イテレータを進める
				++it;
			}
		}

		for (const auto& point : points)
		{
			Circle{ point, 30 }.draw();
		}
	}
}
