# include <Siv3D.hpp>

void Main()
{
	// 初期データを与えないと、空のフォントになる
	Font fontA;

	if (not fontA)
	{
		Print << U"fontA is empty";
	}

	// フォントファイルの読み込みに失敗すると、空のフォントになる
	Font fontB{ 40, U"aaa/bbb.ttf" };

	if (not fontB)
	{
		Print << U"fontB is empty";
	}

	while (System::Update())
	{
		// 何も描かれない
		fontA(U"Hello, Siv3D!").draw(100, 100);

		// 何も描かれない
		fontB(U"Hello, Siv3D!").draw(100, 200);
	}
}
