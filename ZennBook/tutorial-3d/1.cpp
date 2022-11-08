# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);
	const ColorF backgroundColor = ColorF{ 0.4, 0.6, 0.8 }.removeSRGBCurve();
	const Texture uvChecker{ U"example/texture/uv.png", TextureDesc::MippedSRGB };
	const MSRenderTexture renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes };
	DebugCamera3D camera{ renderTexture.size(), 30_deg, Vec3{ 10, 16, -32 } };

	while (System::Update())
	{
		camera.update(2.0);
		Graphics3D::SetCameraTransform(camera);

		// 3D 描画
		{
			const ScopedRenderTarget3D target{ renderTexture.clear(backgroundColor) };

			// 中心 (0,0,0) 一辺の幅が 64 の平面にテクスチャ uvChecker を貼って描画
			Plane{ 64 }.draw(uvChecker);

			// 中心　(-8,2,0), 一辺の幅が 8 の床を黄色 (sRGB カーブ除去済み）で描画
			Plane{ Vec3{ -8, 2, 0 }, 8 }.draw(Linear::Palette::Yellow);

			Plane{ Vec3{ -8, 4, 0 }, 6 }.draw(Linear::Palette::Orange);

			Plane{ Vec3{ -8, 6, 0 }, 4 }.draw(Linear::Palette::Red);

			Plane{ Vec3{ 8, 2, 8 }, 16, 8 }.draw(ColorF{ 0.2, 0.3, 0.4 }.removeSRGBCurve());

			Plane{ Vec3{ 8, 2, -8 }, 16 }.draw(uvChecker);
		}

		// 3D シーンを 2D シーンに描画
		{
			Graphics3D::Flush();
			renderTexture.resolve();
			Shader::LinearToScreen(renderTexture);
		}
	}
}
