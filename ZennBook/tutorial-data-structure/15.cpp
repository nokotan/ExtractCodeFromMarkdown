# include <Siv3D.hpp>

void Main()
{
	// 最初は無効値
	Optional<Point> pos;

	if (not pos)
	{
		Print << U"not pos";
	}

	// 有効値を持たせる
	pos = Point{ 100, 200 };

	if (pos)
	{
		Print << *pos;
	}

	// 無効値にする
	pos.reset();

	Print << pos.has_value();

	// pos が無効値の場合 Point{ -1, -1 } を返す
	Print << pos.value_or(Point{ -1, -1 });

	pos = Point{ 100, 200 };

	Print << pos.value_or(Point{ -1, -1 });

	Print << pos->x;

	Print << pos->y;

	// 無効値を代入する
	pos = none;

	Print << pos.has_value();

	while (System::Update())
	{

	}
}
