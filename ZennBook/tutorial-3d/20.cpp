# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);
	const ColorF backgroundColor = ColorF{ 0.4, 0.6, 0.8 }.removeSRGBCurve();
	const Texture uvChecker{ U"example/texture/uv.png", TextureDesc::MippedSRGB };
	const MSRenderTexture renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes };
	DebugCamera3D camera{ renderTexture.size(), 30_deg, Vec3{ 10, 16, -32 } };

	ColorF ambientColor = Graphics3D::DefaultGlobalAmbientColor;
	ColorF sunColor = Graphics3D::DefaultSunColor;
	double direction = 90_deg;
	double elevation = 45_deg;

	while (System::Update())
	{
		camera.update(2.0);
		Graphics3D::SetCameraTransform(camera);

		// 環境光を設定
		Graphics3D::SetGlobalAmbientColor(ambientColor);

		// 太陽光の色を設定
		Graphics3D::SetSunColor(sunColor);

		// 太陽の方向を設定
		const Vec3 sunDirection = Spherical{ 1.0, (90_deg - elevation), (-direction +90_deg) };
		Graphics3D::SetSunDirection(sunDirection);

		// 3D 描画
		{
			const ScopedRenderTarget3D target{ renderTexture.clear(backgroundColor) };

			Plane{ 64 }.draw(uvChecker);
			Box{ -8,2,0,4 }.draw(ColorF{ 0.8, 0.6, 0.4 }.removeSRGBCurve());
			Sphere{ 0,2,0,2 }.draw();
			Cylinder{ 8, 2, 0, 2, 4 }.draw(ColorF{ 0.6, 0.4, 0.8 }.removeSRGBCurve());

			// 太陽の方向を赤い線分で可視化
			Line3D{ Vec3{0, 2, 0}, (Vec3{0,2,0} + sunDirection * 5) }.draw(Linear::Palette::Red);
		}

		// 3D シーンを 2D シーンに描画
		{
			Graphics3D::Flush();
			renderTexture.resolve();
			Shader::LinearToScreen(renderTexture);
		}

		SimpleGUI::Headline(U"Ambient", Vec2{ 20, 20 });
		SimpleGUI::Slider(U"R: {:.2f}"_fmt(ambientColor.r), ambientColor.r, Vec2{ 20, 60 });
		SimpleGUI::Slider(U"G: {:.2f}"_fmt(ambientColor.g), ambientColor.g, Vec2{ 20, 100 });
		SimpleGUI::Slider(U"B: {:.2f}"_fmt(ambientColor.b), ambientColor.b, Vec2{ 20, 140 });

		SimpleGUI::Headline(U"Sun", Vec2{ 240, 20 });
		SimpleGUI::Slider(U"R: {:.2f}"_fmt(sunColor.r), sunColor.r, Vec2{ 240, 60 });
		SimpleGUI::Slider(U"G: {:.2f}"_fmt(sunColor.g), sunColor.g, Vec2{ 240, 100 });
		SimpleGUI::Slider(U"B: {:.2f}"_fmt(sunColor.b), sunColor.b, Vec2{ 240, 140 });

		SimpleGUI::Headline(U"Sun Direction", Vec2{ 240, 20 });
		SimpleGUI::Slider(U"d: {:.0f}°"_fmt(Math::ToDegrees(direction)), direction, 0_deg, 360_deg, Vec2{ 460, 60 });
		SimpleGUI::Slider(U"e: {:.1f}°"_fmt(Math::ToDegrees(elevation)), elevation, 0_deg, 90_deg, Vec2{ 460, 100 });
	}
}
