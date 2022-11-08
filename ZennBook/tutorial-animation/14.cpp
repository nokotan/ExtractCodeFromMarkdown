# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(Palette::White);

	// スタート位置
	Vec2 from{ 100, 100 };

	// ゴール位置
	Vec2 to{ 700, 500 };

	Stopwatch stopwatch{ StartImmediately::Yes };

	while (System::Update())
	{
		// 移動の割合 0.0～1.0
		const double t = Min(stopwatch.sF(), 1.0);

		// スタート位置からゴール位置へ t の割合だけ進んだ位置
		const Vec2 pos = from.lerp(to, t);

		if (MouseL.down())
		{
			// スタート位置を現在の位置に
			from = pos;

			// ゴール位置をマウスカーソルの位置に
			to = Cursor::Pos();

			stopwatch.restart();
		}

		Circle{ pos, 40 }.draw(ColorF{ 0.25 });
		Circle{ to, 50 }.drawFrame(5, ColorF{ 0.25 });
	}
}
