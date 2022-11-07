# include <Siv3D.hpp>

void Main()
{
	bool clip = false;

	while (System::Update())
	{
		ClearPrint();
		Print << Cursor::Pos();

		if (SimpleGUI::CheckBox(clip, U"clip", Vec2{ 100, 20 }))
		{
			if (clip)
			{
				// マウスカーソルの移動をウィンドウのクライアント領域上に制限
				Cursor::ClipToWindow(true);
			}
			else
			{
				// 制限を解除
				Cursor::ClipToWindow(false);
			}
		}
	}
}
