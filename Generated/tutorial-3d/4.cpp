# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);

	const ColorF backgroundColor = ColorF{ 0.4, 0.6, 0.8 }.removeSRGBCurve();
	const Texture uvChecker{ U"example/texture/uv.png", TextureDesc::MippedSRGB };
	const Texture earthTexture{ U"example/texture/earth.jpg", TextureDesc::MippedSRGB };
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

			// 中心 (0,2,0) 半径が 2 の球にテクスチャ earthTexture を貼って描画
			Sphere{ 0, 2, 0, 2 }.draw(earthTexture);

			for (auto i : Range(-4, 4))
			{
				Sphere{ (i * 4), 1, 8, 1 }.draw(HSV{ i * 20 }.removeSRGBCurve());
			}

			for (auto i : Range(-4, 4))
			{
				Sphere{ (i * 4), 1, -8, 0.5 }.draw(ColorF{ 0.5 + i * 0.125 }.removeSRGBCurve());
			}
		}

		// 3D シーンを 2D シーンに描画
		{
			Graphics3D::Flush();
			renderTexture.resolve();
			Shader::LinearToScreen(renderTexture);
		}
	}
}
