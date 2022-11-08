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

			Plane{ 64 }.draw(uvChecker);

			Line3D{ Vec3{0, 0, 0}, Vec3{0, 8, 0} }.draw(ColorF{ 0.25 }.removeSRGBCurve());

			for (auto z : Range(-4, 4))
			{
				Line3D{ Vec3{-8, 4, (z * 4)}, Vec3{8, 4, (z * 4)} }.draw(Linear::Palette::Red);
			}

			Line3D{ Vec3{8, 4, 16}, Vec3{-8, 4, -16} }.draw();
		}

		// 3D シーンを 2D シーンに描画
		{
			Graphics3D::Flush();
			renderTexture.resolve();
			Shader::LinearToScreen(renderTexture);
		}
	}
}
