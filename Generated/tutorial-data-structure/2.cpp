# include <Siv3D.hpp>

void Main()
{
	Array<Vec2> points =
	{
		Vec2{ 100, 100 }, Vec2{ 200, 200 },
		Vec2{ 300, 300 }, Vec2{ 400, 400 }
	};

	// 0 番目の要素にアクセス
	Print << points[0];

	// 2 番目の要素にアクセス
	Print << points[2];

	// 先頭の要素にアクセス
	Print << points.front();

	// 末尾の要素にアクセス
	Print << points.back();

	while (System::Update())
	{

	}
}
