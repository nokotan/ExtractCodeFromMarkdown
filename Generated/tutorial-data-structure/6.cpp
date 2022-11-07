# include <Siv3D.hpp>

void Main()
{
	Array<int32> values = { 1, 6, 3, 5, 2, 10 };
	Print << U"before: " << values;
	// 5 よりも大きい要素を削除
	values.remove_if([](int32 n) { return (5 < n); });
	Print << U"after: " << values;

	Array<Vec2> points =
	{
		Vec2{ 100, 100 }, Vec2{ 200, 200 },
		Vec2{ 300, 300 }, Vec2{ 400, 400 }
	};
	Print << U"before: " << points;
	// y 成分が 250 より大きい要素を削除
	points.remove_if([](const Vec2& v) { return (250 < v.y); });
	Print << U"after: " << points;

	while (System::Update())
	{

	}
}
