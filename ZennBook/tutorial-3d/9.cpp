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
		const double t = Scene::Time();

		camera.update(2.0);
		Graphics3D::SetCameraTransform(camera);

		// 3D 描画
		{
			const ScopedRenderTarget3D target{ renderTexture.clear(backgroundColor) };

			Plane{ 64 }.draw(uvChecker);

			// 中心 (0,2,0) 各辺の長さが 4, Y 軸に沿って回転した
			// ボックスにテクスチャ woodTexture を貼って描画
			OrientedBox{ Vec3{0, 2, 0}, 4, Quaternion::RotateY(t * 30_deg) }.draw(woodTexture);

			for (auto i : Range(-4, 4))
			{
				// 回転の乗算で複数の回転を合成できる
				const Quaternion orientation = (Quaternion::RotateZ(i * 20_deg) * Quaternion::RotateX(t * 30_deg));

				OrientedBox{ Vec3{ (i * 4), 2, 8}, 1, 4, 1, orientation }
					.draw(HSV{ i * 20 }.removeSRGBCurve());
			}

			OrientedBox{ Vec3{ 0, 4, -8 }, 1, 8, 1, Quaternion::RotateZ(t * 60_deg) }.draw();
			OrientedBox{ Vec3{ 0, 4, -8 }, 8, 1, 1, Quaternion::RotateZ(t * 60_deg) }.draw();
		}

		// 3D シーンを 2D シーンに描画
		{
			Graphics3D::Flush();
			renderTexture.resolve();
			Shader::LinearToScreen(renderTexture);
		}
	}
}
