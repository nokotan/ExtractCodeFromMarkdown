# include <Siv3D.hpp>

void Main()
{
	Scene::SetResizeMode(ResizeMode::Keep);
	Window::SetStyle(WindowStyle::Sizable);

	while (System::Update())
	{
		ClearPrint();
		Print << U"frameBufferSize: " << Window::GetState().frameBufferSize;
		Print << U"virtualSize: " << Window::GetState().virtualSize;
		Print << U"scene size: " << Scene::Size();

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
	}
}
