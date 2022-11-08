# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);
	const ColorF backgroundColor = ColorF{ 0.4, 0.6, 0.8 }.removeSRGBCurve();
	const Texture uvChecker{ U"example/texture/uv.png", TextureDesc::MippedSRGB };
	const MSRenderTexture renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes };

	Vec3 eyePosition{ 0, 16, -32 };
	Vec3 focusPosition{ 0, 2, 0 };

	BasicCamera3D camera{ renderTexture.size(), 30_deg, Vec3{ 0, 16, -32 }, Vec3{ 0, 16, -32 } };

	while (System::Update())
	{
		const double t = Scene::Time();
		eyePosition.x = (Math::Sin(t * 30_deg) * 20.0);
		focusPosition.x = eyePosition.x;

		ClearPrint();
		Print << U"eyePositon: {:.1f}"_fmt(eyePosition);
		Print << U"focusPosition: {:.1f}"_fmt(focusPosition);

		// 位置・注目点情報を更新
		camera.setView(eyePosition, focusPosition);

		Graphics3D::SetCameraTransform(camera);

		// 3D 描画
		{
			const ScopedRenderTarget3D target{ renderTexture.clear(backgroundColor) };
			Plane{ 64 }.draw(uvChecker);
			Box{ -8,2,0,4 }.draw(ColorF{ 0.8, 0.6, 0.4 }.removeSRGBCurve());
			Sphere{ 0,2,0,2 }.draw(ColorF{ 0.4, 0.8, 0.6 }.removeSRGBCurve());
			Cylinder{ 8, 2, 0, 2, 4 }.draw(ColorF{ 0.6, 0.4, 0.8 }.removeSRGBCurve());
		}

		// 3D シーンを 2D シーンに描画
		{
			Graphics3D::Flush();
			renderTexture.resolve();
			Shader::LinearToScreen(renderTexture);
		}
	}
}
