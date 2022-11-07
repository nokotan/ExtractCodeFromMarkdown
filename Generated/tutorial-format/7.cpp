# include <Siv3D.hpp>

void Main()
{
	const int32 a = Parse<int32>(U"123");
	const double b = Parse<double>(U"-3.14159");
	const Point c = Parse<Point>(U"(10, 20)");

	Print << a;
	Print << b;
	Print << c;

	try
	{
		const Point d = Parse<Point>(U"(0,0)");
		const Point e = Parse<Point>(U"(20, 40)");
		const Point f = Parse<Point>(U"123"); // 失敗して例外を投げる
	}
	catch (const ParseError& e)
	{
		// 例外の詳細を取得して表示
		Print << e.what();
	}

	while (System::Update())
	{

	}
}
