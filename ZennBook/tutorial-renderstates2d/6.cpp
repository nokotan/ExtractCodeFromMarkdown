#include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	const Texture textureWindmill{ U"example/windmill.png" };
	const Texture textureSiv3DKun{ U"example/siv3d-kun.png" };

	// シザー矩形を設定
	Graphics2D::SetScissorRect(Rect{ 100, 100, 300, 200 });

	while (System::Update())
	{
		RasterizerState rs = RasterizerState::Default2D;
		// シザー矩形を有効化
		rs.scissorEnable = true;
		const ScopedRenderStates2D rasterizer{ rs };

		textureWindmill.draw(40, 20);
		textureSiv3DKun.draw(200, 100);
	}
}
