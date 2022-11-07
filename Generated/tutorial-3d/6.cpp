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

			// 中心 (0,2,0) 半径 2, 高さが 4 の円柱にテクスチャ woodTexture を貼って描画
			Cylinder{ Vec3{0, 2, 0}, 2, 4 }.draw(woodTexture);

			for (auto i : Range(-4, 4))
			{
				// 2 点を指定して円柱を作成
				Cylinder{ Vec3{ (i * 4), (8 + i), 8}, Vec3{(i * 4), 0, 8}, 1 }
					.draw(HSV{ i * 20 }.removeSRGBCurve());
			}

			// 2 点を指定して円柱を作成
			Cylinder{ Vec3{-8, 0.5, -8}, Vec3{8, 4, -4}, 0.5 }.draw();
			Cylinder{ Vec3{ 8, 0.25, -8 }, Vec3{8, 0, -8}, 4 }.draw(Linear::Palette::Gray);
		}

		// 3D シーンを 2D シーンに描画
		{
			Graphics3D::Flush();
			renderTexture.resolve();
			Shader::LinearToScreen(renderTexture);
		}
	}
}
