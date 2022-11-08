# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);
	Graphics3D::SetGlobalAmbientColor(ColorF{ 0.25 });
	const ColorF backgroundColor = ColorF{ 0.4, 0.6, 0.8 }.removeSRGBCurve();
	const MSRenderTexture renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes };
	DebugCamera3D camera{ renderTexture.size(), 30_deg, Vec3{ 10, 16, -32 } };

	const Plane floorPlane{ 20 };
	Image image{ 1000, 1000, Palette::White };
	DynamicTexture texture{ image, TextureDesc::MippedSRGB };
	Optional<Vec2> previousPenPos;

	// 太陽光の影響を与えないようにする
	Graphics3D::SetGlobalAmbientColor(ColorF{ 1.0 });
	Graphics3D::SetSunColor(ColorF{ 0.0 });

	while (System::Update())
	{
		camera.update(2.0);
		Graphics3D::SetCameraTransform(camera);

		// 3D
		{
			const Ray ray = camera.screenToRay(Cursor::PosF());
			const ScopedRenderTarget3D target{ renderTexture.clear(backgroundColor) };

			if (const auto pos = ray.intersectsAt(floorPlane))
			{
				Sphere{ *pos, 0.2 }.draw(Linear::Palette::Orange);
				const Vec2 penPos = pos->xz();

				if (MouseL.pressed())
				{
					const Vec2 from = (previousPenPos ? *previousPenPos : penPos);
					const Vec2 to = penPos;
					previousPenPos = penPos;
					Line{ (from * Vec2{ 50, -50 }), (to * Vec2{ 50, -50 }) }
						.movedBy(500, 500)
						.overwrite(image, 5, ColorF{ Palette::Orange }.removeSRGBCurve());
					texture.fill(image);
				}
				else
				{
					previousPenPos.reset();
				}
			}
			else
			{
				previousPenPos.reset();
			}

			floorPlane.draw(texture);
		}

		// RenderTexture を 2D シーンに描画
		{
			Graphics3D::Flush();
			renderTexture.resolve();
			Shader::LinearToScreen(renderTexture);
		}
	}
}
