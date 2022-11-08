# include <Siv3D.hpp>

void Main()
{
	Array<int32> values = { 20, 30, 40, 50 };
	Array<Vec2> points;

	// 配列が空かどうかを表示
	Print << values.isEmpty();
	Print << points.isEmpty();

	if (values)
	{
		Print << U"A";
	}

	if (not points)
	{
		Print << U"B";
	}

	while (System::Update())
	{

	}
}
