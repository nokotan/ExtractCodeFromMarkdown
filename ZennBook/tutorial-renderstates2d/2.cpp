# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	const Texture textureWindmill{ U"example/windmill.png" };
	const Texture textureSiv3DKun{ U"example/siv3d-kun.png" };
	ColorF color{ 1.0, 1.0, 1.0, 1.0 };

	while (System::Update())
	{
		{
			// 描画時に色を乗算
			const ScopedColorMul2D colorMul{ color };

			textureWindmill.draw(40, 20);
			textureSiv3DKun.draw(400, 100);
		}

		SimpleGUI::Slider(U"R", color.r, Vec2{ 620, 20 }, 40);
		SimpleGUI::Slider(U"G", color.g, Vec2{ 620, 60 }, 40);
		SimpleGUI::Slider(U"B", color.b, Vec2{ 620, 100 }, 40);
		SimpleGUI::Slider(U"A", color.a, Vec2{ 620, 140 }, 40);
	}
}
