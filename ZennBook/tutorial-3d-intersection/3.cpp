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
			boxes << Box{ (x * 4), 2, (z * 4), 3, 4, 1 };
		}
	}

	while (System::Update())
	{
		ClearPrint();
		camera.update(2.0);
		Graphics3D::SetCameraTransform(camera);

		// 3D
		{
			const Ray ray = camera.screenToRay(Cursor::PosF());
			const ScopedRenderTarget3D target{ renderTexture.clear(backgroundColor) };

			Plane{ 64 }.draw(uvChecker);

			// 交差し、もっとも手前にあるボックスのインデックス
			Optional<size_t> boxIndex;
			double minDistance = Math::Inf;

			for (auto [i, box] : Indexed(boxes))
			{
				if (const auto distance = ray.intersects(box))
				{
					if (*distance < minDistance)
					{
						minDistance = *distance;
						boxIndex = i;
					}
				}
			}

			for (auto [i, box] : Indexed(boxes))
			{
				if (i == boxIndex)
				{
					box.draw(Linear::Palette::Orange);
				}
				else
				{
					box.draw();
				}
			}

			if (boxIndex)
			{
				Cursor::RequestStyle(CursorStyle::Hand);

				// 距離から交差地点を計算
				const Vec3 pos = ray.point_at(minDistance);
				Sphere{ pos, 0.2 }.draw(Linear::Palette::Red);

				Print << *boxIndex;
				Print << pos;
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
