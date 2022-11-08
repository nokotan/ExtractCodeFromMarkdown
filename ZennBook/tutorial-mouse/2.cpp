# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		ClearPrint();

		// マウスカーソルの位置をスクリーン座標で表示
		Print << Cursor::ScreenPos();
	}
}
