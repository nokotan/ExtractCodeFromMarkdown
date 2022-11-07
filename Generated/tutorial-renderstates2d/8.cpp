# include <Siv3D.hpp>

void Main()
{
	const Texture textureWindmill{ U"example/windmill.png", TextureDesc::Mipped };
	const Texture textureSiv3DKun{ U"example/siv3d-kun.png", TextureDesc::Mipped };
	constexpr Circle circle{ 200, 400, 60 };

	size_t index = 0;

	while (System::Update())
	{
		// 何もしない行列
		Mat3x2 mat = Mat3x2::Identity();

		if (index == 0)
		{

		}
		else if (index == 1)
		{
			// シーンの中心を基準に 1.5 倍拡大
			mat = Mat3x2::Scale(1.5, Scene::Center());
		}
		else if (index == 2)
		{
			// (50, 50) 移動
			mat = Mat3x2::Translate(50, 50);
		}
		else if (index == 3)
		{
			// シーンの中心を回転の軸にして 30° 回転
			mat = Mat3x2::Rotate(30_deg, Scene::Center());
		}
		else if (index == 4)
		{
			// シーンの中心を回転の軸にして徐々に回転しながら拡大
			mat = Mat3x2::Rotate(Scene::Time() * 5_deg, Scene::Center())
				.scaled(0.5 + Scene::Time() * 0.03, Scene::Center());
		}

		{
			// 座標変換行列を適用
			const Transformer2D transformer{ mat, TransformCursor::Yes };

			textureWindmill.draw(0, 0);

			textureSiv3DKun.draw(360, 100);

			circle.draw(circle.mouseOver() ? Palette::Red : Palette::Yellow);
		}

		SimpleGUI::RadioButtons(index, { U"Identity", U"Scale", U"Translate", U"Rotate", U"Roatate * Scale" }, Vec2{ 600, 20 });
	}
}
