# include <Siv3D.hpp>

void Main()
{
	Vec2 pos = Scene::Center();

	while (System::Update())
	{
		ClearPrint();

		// マウスホイールのスクロール量
		Print << Mouse::Wheel();

		// マウスの水平ホイールのスクロール量
		Print << Mouse::WheelH();

		pos.y -= (Mouse::Wheel() * 10);
		pos.x += (Mouse::WheelH() * 10);

		RectF{ Arg::center = pos, 200 }.draw();
	}
}
