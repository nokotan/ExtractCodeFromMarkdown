# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		// 座標 (100, 100) から (400, 150) まで太さ 4px の線分を描く
		Line{ 100, 100, 400, 150 }.draw(4, Palette::Yellow);

		// 座標 (400, 300) からマウスカーソルの座標まで太さ 10px の線分を描く
		Line{ 400, 300, Cursor::Pos() }.draw(10, Palette::Skyblue);

		// 通常の線
		Line{ 100, 400, 700, 400 }.draw(12, Palette::Orange);

		// 両端が丸い線
		Line{ 100, 450, 700, 450 }.draw(LineStyle::RoundCap, 12, Palette::Orange);

		// 四角いドットの線
		Line{ 100, 500, 700, 500 }.draw(LineStyle::SquareDot, 12, Palette::Orange);

		// 丸いドットの線
		Line{ 100, 550, 700, 550 }.draw(LineStyle::RoundDot, 12, Palette::Orange);
	}
}
