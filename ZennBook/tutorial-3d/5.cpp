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

			// 中心 (0,2,0) 各辺の長さが 4 のボックスにテクスチャ woodTexture を貼って描画
			Box{ Vec3{0, 2, 0}, 4 }.draw(woodTexture);

			for (auto i : Range(-4, 4))
			{
				Box{ (i * 4), 2, 8, 1, 4, 1 }.draw(HSV{ i * 20 }.removeSRGBCurve());
			}

			// 2 点を指定して直方体を作成
			Box::FromPoints(Vec3{ -8, 2, -8 }, Vec3{ 0, 0, -12 }).draw();
			Box::FromPoints(Vec3{ 0, 2, -8 }, Vec3{ 4, 0, -16 }).draw();
		}

		// 3D シーンを 2D シーンに描画
		{
			Graphics3D::Flush();
			renderTexture.resolve();
			Shader::LinearToScreen(renderTexture);
		}
	}
}
