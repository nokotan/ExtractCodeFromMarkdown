# include <Siv3D.hpp>

void Main()
{
	Polygon polygon;

	while (System::Update())
	{
		const Rect rect{ Arg::center = Cursor::Pos(), 100 };

		if (MouseL.down())
		{
			// polygon に rect を追加する
			// ただし、polygon と rect がつながらない場合は失敗して false を返す
			polygon.append(rect);
		}

		polygon
			.draw(Palette::Skyblue)
			.drawWireframe(1, Palette::White);

		rect.drawFrame(1, 0, Palette::Skyblue);
	}
}
