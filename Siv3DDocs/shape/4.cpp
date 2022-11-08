# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		// 中心座標がマウスの座標, 半径 100 の円を描く
		Circle{ Cursor::Pos(), 100 }.draw();
	}
}
