# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		ClearPrint();

		// スクリーン上のウィンドウの位置を表示
		Print << Window::GetPos();

		if (SimpleGUI::Button(U"(0, 0)", Vec2{ 200, 20 }))
		{
			// ウィンドウをスクリーンの (0, 0) に移動
			Window::SetPos(0, 0);
		}

		if (SimpleGUI::Button(U"(200, 200)", Vec2{ 300, 20 }))
		{
			// ウィンドウをスクリーンの (200, 200) に移動
			Window::SetPos(200, 200);
		}
	}
}
