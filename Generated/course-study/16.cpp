# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		// 左から順に 7 つの円を描く
		Circle{ 100, 200, 40 }.draw();

		Circle{ 200, 200, 40 }.draw(Palette::Green);

		Circle{ 300, 200, 40 }.draw(Palette::Skyblue);

		Circle{ 400, 200, 40 }.draw(ColorF{ 1.0, 0.8, 0.0 });

		Circle{ 500, 200, 40 }.draw(Color{ 255, 127, 127 });

		Circle{ 600, 200, 40 }.draw(HSV{ 160.0, 1.0, 1.0 });

		Circle{ 700, 200, 40 }.draw(HSV{ 160.0, 0.75, 1.0 });

		// 半透明の円
		Circle{ Cursor::Pos(), 80 }.draw(ColorF{ 0.0, 0.5, 1.0, 0.8 });
	}
}
