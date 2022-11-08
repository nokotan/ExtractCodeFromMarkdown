# include <Siv3D.hpp>

void Main()
{
	Array<int32> values = { 1, 6, 3, 5, 2, 10 };

	Print << values;

	Array<Vec2> points =
	{
		Vec2{ 100, 100 }, Vec2{ 200, 200 },
		Vec2{ 300, 300 }, Vec2{ 400, 400 }
	};

	Print << points;

	while (System::Update())
	{

	}
}
