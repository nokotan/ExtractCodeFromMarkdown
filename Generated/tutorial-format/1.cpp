# include <Siv3D.hpp>

void Main()
{
	Print << U"Siv{}D"_fmt(3);

	Print << U"{}/{}/{}"_fmt(2020, 12, 31);

	Print << U"Hello, {}!"_fmt(U"Siv3D");

	Print << U"position: {}, color: {}"_fmt(Point{ 23, 45 }, ColorF{ 0.7, 0.8, 0.9 });

	// '{', '}' を使いたい場合は "{{", "}}" を使う 
	Print << U"{{abc}} {}"_fmt(123);

	while (System::Update())
	{

	}
}
