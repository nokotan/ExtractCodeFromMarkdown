# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		// 中心座標 (マウスの X 座標, 300), 半径 100 の円を描く
		Circle{ Cursor::Pos().x, 300, 100 }.draw();
	}
}
