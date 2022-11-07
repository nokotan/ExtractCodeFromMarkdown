# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);
	Graphics3D::SetGlobalAmbientColor(ColorF{ 0.25 });
	const ColorF backgroundColor = ColorF{ 0.4, 0.6, 0.8 }.removeSRGBCurve();
	const Texture uvChecker{ U"example/texture/uv.png", TextureDesc::MippedSRGB };
	const MSRenderTexture renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes };
	DebugCamera3D camera{ renderTexture.size(), 30_deg, Vec3{ 10, 16, -32 } };

	Array<Box> boxes;
	for (auto z : Range(-3, 3))
	{
		for (auto x : Range(-6, 6))
		{
			boxes << Box{ (x * 3), 2, (z * 3), 1 };
		}
	}

	while (System::Update())
	{
		camera.update(2.0);
		Graphics3D::SetCameraTransform(camera);

		// 3D
		{
			const Ray ray = camera.screenToRay(Cursor::PosF());
			const ScopedRenderTarget3D target{ renderTexture.clear(backgroundColor) };
			Plane{ 64 }.draw(uvChecker);

			const Sphere sphere{
				(Math::Sin(Scene::Time() * 15_deg) * 16), 2, (Math::Sin(Scene::Time() * 10_deg) * 8), 4 };

			for (const auto& box : boxes)
			{
				const bool intersects = sphere.intersects(box);
				box.draw(intersects ? Linear::Palette::Orange : Linear::Palette::White);
			}

			{
				const ScopedRenderStates3D rasterizer{ RasterizerState::WireframeCullNone };
				sphere.draw();
			}
		}

		// RenderTexture を 2D シーンに描画
		{
			Graphics3D::Flush();
			renderTexture.resolve();
			Shader::LinearToScreen(renderTexture);
		}
	}
}
