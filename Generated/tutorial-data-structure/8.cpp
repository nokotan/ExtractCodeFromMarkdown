# include <Siv3D.hpp>

void Main()
{
	// 10 個の 5
	Array<int32> values(10, 5);

	Print << values;

	// 5 個の Vec2{ 0, 0 }
	Array<Vec2> points(5, Vec2{ 0, 0 });

	Print << points;

	while (System::Update())
	{

	}
}
