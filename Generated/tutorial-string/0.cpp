# include <Siv3D.hpp>

void Main()
{
	const String s = U"Siv3D";

	Print << s;

	// 文字列の長さ
	Print << s.size();

	while (System::Update())
	{

	}
}
