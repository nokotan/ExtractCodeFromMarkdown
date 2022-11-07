# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	while (System::Update())
	{
		const ScopedViewport2D viewport{ 400, 300, 400, 300 };

		// マウスカーソル座標だけ移動させる
		const Transformer2D transformer{ Mat3x2::Identity(), Mat3x2::Translate(400, 300) };

		Circle{ 200, 150, 200 }.draw();
		Circle{ Cursor::PosF(), 40 }.draw(Palette::Orange);

		if (SimpleGUI::Button(U"Button", Vec2{ 20,20 }))
		{
			Print << U"Pushed";
		}
	}
}
