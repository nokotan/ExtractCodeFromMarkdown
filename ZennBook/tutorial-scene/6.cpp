# include <Siv3D.hpp>

void Main()
{
	Scene::SetResizeMode(ResizeMode::Keep);

	// シーンを 1600x1200 にリサイズ
	Scene::Resize(1600, 1200);

	while (System::Update())
	{
		ClearPrint();
		Print << U"frameBufferSize: " << Window::GetState().frameBufferSize;
		Print << U"virtualSize: " << Window::GetState().virtualSize;
		Print << U"scene size: " << Scene::Size();

		// マウスカーソルの座標を Vec2 型で取得
		Print << Cursor::PosF();

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
