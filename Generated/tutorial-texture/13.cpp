# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	const Texture textureWindmill{ U"example/windmill.png" };

	const Texture textureSiv3DKun{ U"example/siv3d-kun.png" };

	while (System::Update())
	{
		textureWindmill.draw(40, 20);

		// アルファ成分を 0.0～1.0 の間で変化させる
		textureSiv3DKun.draw(400, 100, ColorF{ 1.0, Periodic::Sine0_1(2s) });
	}
}
