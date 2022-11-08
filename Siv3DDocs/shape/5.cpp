# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		// 中心座標 (マウスの X 座標, マウスの Y 座標), 半径 100 の円を描く
		Circle{ Cursor::Pos().x, Cursor::Pos().y, 100 }.draw();
	}
}
