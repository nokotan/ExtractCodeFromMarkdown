# include <Siv3D.hpp>

void Main()
{
	// ウィンドウの最大化を可能にする
	Window::SetStyle(WindowStyle::Sizable);

	// 最小化中にカウントする変数
	int32 count = 0;

	while (System::Update())
	{
		ClearPrint();
		Print << U"frameBufferSize: " << Window::GetState().frameBufferSize;
		Print << U"virtualSize: " << Window::GetState().virtualSize;
		Print << U"scene size: " << Scene::Size();
		Print << U"minimized: " << count;
		Print << U"maximized: " << Window::GetState().maximized;

		if (Window::GetState().minimized)
		{
			++count;
		}

		// 100px サイズの市松模様
		for (int32 y = 0; y < 50; ++y)
		{
			for (int32 x = 0; x < 50; ++x)
			{
				if ((x + y) % 2)
				{
					Rect{ x * 100, y * 100, 100 }.draw(ColorF{ 0.2, 0.3, 0.4 });
				}
			}
		}

		if (SimpleGUI::Button(U"Minimize", Vec2{ 300, 20 }))
		{
			// ウィンドウを最小化
			Window::Minimize();
		}

		if (SimpleGUI::Button(U"Maximize", Vec2{ 300, 60 }))
		{
			// ウィンドウを最大化
			Window::Maximize();
		}

		if (SimpleGUI::Button(U"Restore", Vec2{ 300, 100 }))
		{
			// 最小化 / 最大化されたウィンドウを元のサイズに戻す
			Window::Restore();
		}
	}
}
