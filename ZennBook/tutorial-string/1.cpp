# include <Siv3D.hpp>

void Main()
{
	String s = U"Siv3D";

	// 0 番目の要素
	Print << s[0];

	// 2 番目の要素
	Print << s[2];

	// 先頭の要素
	Print << s.front();

	// 末尾の要素
	Print << s.back();

	s[3] = U'4';

	Print << s;

	while (System::Update())
	{

	}
}
