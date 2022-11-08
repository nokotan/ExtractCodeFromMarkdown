# include <Siv3D.hpp>

void Main()
{
	const int32 a = Parse<int32>(U"123");
	const double b = Parse<double>(U"-3.14159");
	const Point c = Parse<Point>(U"(10, 20)");

	Print << a;
	Print << b;
	Print << c;

	while (System::Update())
	{

	}
}
