# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		ClearPrint();
		Print << U"frameBufferSize: " << Window::GetState().frameBufferSize;
		Print << U"virtualSize: " << Window::GetState().virtualSize;
		Print << U"scene size: " << Scene::Size();
		Print << U"fullscreen: " << Window::GetState().fullscreen;

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

		if (Window::GetState().fullscreen)
		{
			if (SimpleGUI::Button(U"Window mode", Vec2{ 300, 20 }))
			{
				// ウィンドウモードにする
				Window::SetFullscreen(false);
			}
		}
		else
		{
			if (SimpleGUI::Button(U"Fullscreen mode", Vec2{ 300, 20 }))
			{
				// フルスクリーンモードにする
				Window::SetFullscreen(true);
			}
		}
	}
}

