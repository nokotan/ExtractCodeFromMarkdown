# include <Siv3D.hpp>

void Main()
{
	const Texture textureWindmill{ U"example/windmill.png" };

	while (System::Update())
	{
		// ワイヤフレーム表示モードに
		const ScopedRenderStates2D rasterizer{ RasterizerState::WireframeCullNone };

		textureWindmill.draw(20, 20);

		Circle{ Scene::Center(), 100 }.draw();

		Shape2D::Star(100, Vec2{ 150, 400 }).draw(Palette::Yellow);
	}
}
