# include <Siv3D.hpp>

void Main()
{
	Font font;

	while (System::Update())
	{
		// フォントが空の状態で、左クリックされたら
		if ((not font) && MouseL.down())
		{
			// フォントを作成して代入
			font = Font{ 40 };
		}

		if (font)
		{
			font(U"Helo, Siv3D!").draw(20, 20);
		}
	}
}
