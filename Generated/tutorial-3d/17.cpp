# include <Siv3D.hpp>

Vec3 GetDirection(double angle)
{
	const Vec2 dir = Circular{ 1.0, angle };
	return{ dir.x, 0.0, -dir.y };
}

Vec3 GetFocusPosition(const Vec3& eyePosition, double angle)
{
	return (eyePosition + GetDirection(angle));
}

void Main()
{
	Window::Resize(1280, 720);
	const ColorF backgroundColor = ColorF{ 0.4, 0.6, 0.8 }.removeSRGBCurve();
	const Texture uvChecker{ U"example/texture/uv.png", TextureDesc::MippedSRGB };
	const MSRenderTexture renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes };

	Vec3 eyePosition{ 0, 2, -16 };
	double angle = 0_deg;
	BasicCamera3D camera{ renderTexture.size(), 30_deg, Vec3{ 0, 16, -32 }, GetFocusPosition(eyePosition, angle) };

	while (System::Update())
	{
		ClearPrint();
		const double deltaTime = Scene::DeltaTime();
		const double speed = (deltaTime * 2.0);

		if (KeyW.pressed())
		{
			eyePosition += (GetDirection(angle) * speed);
		}

		if (KeyA.pressed())
		{
			eyePosition += (GetDirection(angle - 90_deg) * speed);
		}

		if (KeyS.pressed())
		{
			eyePosition += (-GetDirection(angle) * speed);
		}

		if (KeyD.pressed())
		{
			eyePosition += (GetDirection(angle + 90_deg) * speed);
		}

		if (KeyLeft.pressed())
		{
			angle -= (deltaTime * 30_deg);

			if (angle < 0_deg)
			{
				angle += 360_deg;
			}
		}

		if (KeyRight.pressed())
		{
			angle += (deltaTime * 30_deg);

			if (360_deg < angle)
			{
				angle -= 360_deg;
			}
		}

		// 位置・注目点情報を更新
		camera.setView(eyePosition, GetFocusPosition(eyePosition, angle));
		Print << U"angle: {:.1f}°"_fmt(Math::ToDegrees(angle));
		Print << U"direction: {:.2f}"_fmt(GetDirection(angle));
		Print << U"eyePositon: {:.1f}"_fmt(camera.getEyePosition());
		Print << U"focusPosition: {:.1f}"_fmt(camera.getFocusPosition());
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
