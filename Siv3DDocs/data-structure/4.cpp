# include <Siv3D.hpp>

void Main()
{
	String s = U"Siv3D";

	Print << s;

	s = U"Hello";

	Print << s;

	s.clear();

	// 何も表示されない
	Print << s;

	s = U"Siv3D";

	Print << s;

	while (System::Update())
	{

	}
}
