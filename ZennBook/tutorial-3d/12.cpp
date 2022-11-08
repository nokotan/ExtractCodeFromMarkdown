# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);
	const ColorF backgroundColor = ColorF{ 0.4, 0.6, 0.8 }.removeSRGBCurve();
	const Texture uvChecker{ U"example/texture/uv.png", TextureDesc::MippedSRGB };
	const Texture woodTexture{ U"example/texture/wood.jpg", TextureDesc::MippedSRGB };
	const MSRenderTexture renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes };
	DebugCamera3D camera{ renderTexture.size(), 30_deg, Vec3{ 10, 16, -32 } };

	while (System::Update())
	{
		camera.update(2.0);
		Graphics3D::SetCameraTransform(camera);

		// 3D 描画
		{
			const ScopedRenderTarget3D target{ renderTexture.clear(backgroundColor) };

			Plane{ 64 }.draw(uvChecker);

			// 底面の中心 (0,0.0,0), 半径 4, 高さ 4 の円錐を描く
			Cone{ Vec3{0, 0.0, 0}, 4, 4 }.draw(woodTexture);

			for (auto i : Range(-4, 4))
			{
				Cone{ Vec3{ (i * 4), 0.0, 8}, 2, (6.0 + i) }.draw(HSV{ i * 20 }.removeSRGBCurve());
			}

			// from と to を結ぶ 3D の矢印を描く
			const Vec3 from{ -8, 2, -6 }, to{ 4, 6, -4 };
			const Vec3 v = (to - from).normalize();
			const Vec3 headPos = (from + v * (to.distanceFrom(from) - 2.0));
			Cylinder{ from, headPos, 0.2 }.draw(Linear::Palette::Lightgreen);
			Cone{ headPos, to, 0.5 }.draw(Linear::Palette::Lightgreen);
		}

		// 3D シーンを 2D シーンに描画
		{
			Graphics3D::Flush();
			renderTexture.resolve();
			Shader::LinearToScreen(renderTexture);
		}
	}
}
