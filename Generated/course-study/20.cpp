# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		// 長方形の内側に 3px の枠を描く
		Rect{ 100, 100, 100, 30 }
			.drawFrame(3, 0);

		// 長方形の外側に 3px の枠を描く
		Rect{ 220, 100, 100, 30 }
			.drawFrame(0, 3);

		// 長方形と、その内側 3px と外側 3px に枠を描く
		Rect{ 200, 200, 400, 100 }
			.draw(Palette::White)
			.drawFrame(3, 3, Palette::Orange);

		// 円の内側 1px と外側 1px に枠を描く
		Circle{ Cursor::Pos(), 40 }
			.drawFrame(1, 1, Palette::Seagreen);
	}
}
