# include <Siv3D.hpp>

void Main()
{
	const Texture textureWindmill{ U"example/windmill.png" };
	const Texture textureSiv3DKun{ U"example/siv3d-kun.png" };
	ColorF color{ 0.0, 0.0, 0.0, 0.0 };

	while (System::Update())
	{
		{
			// 描画時に色を加算
			const ScopedColorAdd2D colorAdd{ color };

			textureWindmill.draw(40, 20);
			textureSiv3DKun.draw(400, 100);
		}

		SimpleGUI::Slider(U"R", color.r, Vec2{ 620, 20 }, 40);
		SimpleGUI::Slider(U"G", color.g, Vec2{ 620, 60 }, 40);
		SimpleGUI::Slider(U"B", color.b, Vec2{ 620, 100 }, 40);
	}
}
