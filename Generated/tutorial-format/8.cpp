# include <Siv3D.hpp>

void Main()
{
	const int32 a = ParseOr<int32>(U"123", -1);
	const int32 b = ParseOr<int32>(U"???", -1); // 失敗して defaultValue を返す
	const ColorF c = ParseOr<ColorF>(U"123", ColorF{ 0.0, 0.0 }); // 失敗して defaultValue を返す
	const Circle d = ParseOr<Circle>(U"(400, 300, 100)", Circle{ 0, 0, 0 });

	Print << a;
	Print << b;
	Print << c;
	Print << d;

	while (System::Update())
	{

	}
}
