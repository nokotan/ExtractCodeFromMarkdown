# include <Siv3D.hpp>

void Main()
{
	const String a = Format(12345);
	Print << a;

	const String b = Format(true);
	Print << b;

	const String c = Format(1.23456789);
	Print << c;

	const String d = Format(Vec2{ 11, 22 });
	Print << d;

	const Array<int32> values = { 3, 4, 5, 6 };
	const String e = Format(values);
	Print << e;

	const std::array<ColorF, 3> colors =
	{
		ColorF{ 1.0 , 0.0, 0.0 },
		ColorF{ 0.0 , 1.0, 0.0 },
		ColorF{ 0.0 , 0.0, 1.0 },
	};
	const String f = Format(colors);
	Print << f;

	const String g = Format(Rect{ 30, 50, 100, 50 });
	Print << g;

	// (復習) Print は String でなくても使える
	Print << 12345;
	Print << colors;
	Print << Rect{ 30, 50, 100, 50 };

	while (System::Update())
	{

	}
}
