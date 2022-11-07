# include <Siv3D.hpp>

void Main()
{
	const Optional<int32> a = ParseOpt<int32>(U"123");
	const Optional<int32> b = ParseOpt<int32>(U"???"); // 失敗して無効値を返す
	const Optional<ColorF> c = ParseOpt<ColorF>(U"123"); // 失敗して無効値を返す
	const Optional<Circle> d = ParseOpt<Circle>(U"(400, 300, 100)");

	if (a)
	{
		Print << U"a: " << * a;
	}

	if (b)
	{
		Print << U"b: " << *b;
	}

	if (c)
	{
		Print << U"c: " << *c;
	}

	if (d)
	{
		Print << U"d: " << *d;
	}

	while (System::Update())
	{

	}
}
