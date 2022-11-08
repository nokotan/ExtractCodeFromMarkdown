# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		// 座標 (20, 40) を左上の基準位置にして、幅 400, 高さ 100 の長方形を描く 
		Rect{ 20, 40, 400, 100 }.draw();

		// 座標 (100, 200) を左上の基準位置にして、幅が 80 の正方形を描く 
		Rect{ 100, 200, 80 }.draw(Palette::Orange);

		// 座標 (400, 300) を中心の基準位置にして、幅 80, 高さ 40 の長方形を描く
		Rect{ Arg::center(400, 300), 80, 40 }.draw(Palette::Pink);

		// マウスカーソルの座標を中心の基準位置にして、幅が 100 の正方形を描く 
		Rect{ Arg::center(Cursor::Pos()), 100 }.draw(ColorF{ 1.0, 0.0, 0.0, 0.5 });

		// 座標や大きさを浮動小数点数 (小数を含む数）で指定したい場合は RectF
		RectF{ 200.4, 450.3, 390.5, 122.5 }.draw(Palette::Skyblue);
	}
}
