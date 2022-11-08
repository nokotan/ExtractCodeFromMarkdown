# include <Siv3D.hpp>

void Main()
{
	Array<Vec2> points;

	while (System::Update())
	{
		if (MouseL.down())
		{
			// 配列に要素を追加
			points << Cursor::Pos();
		}

		for (const auto& point : points)
		{
			Circle{ point, 10 }.draw();
		}
	}
}
