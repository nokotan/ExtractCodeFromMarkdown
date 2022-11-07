# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		ClearPrint();

		// マウスカーソルがウィンドウのクライアント領域上にあるかを表示
		Print << Cursor::OnClientRect();

		if (Cursor::OnClientRect())
		{
			Scene::SetBackground(ColorF{ 0.4 });
		}
		else
		{
			Scene::SetBackground(ColorF{ 0.2 });
		}
	}
}
