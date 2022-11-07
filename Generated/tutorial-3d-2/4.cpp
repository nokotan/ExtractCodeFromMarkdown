# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);
	const ColorF backgroundColor = ColorF{ 0.4, 0.6, 0.8 }.removeSRGBCurve();
	const Texture uvChecker{ U"example/texture/uv.png", TextureDesc::MippedSRGB };
	const MSRenderTexture renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes };
	DebugCamera3D camera{ renderTexture.size(), 30_deg, Vec3{ 10, 16, -32 } };

	// ビルボード表示する板
	const Mesh billboard{ MeshData::Billboard() };
	const Mesh wideBillboard{ MeshData::Billboard({2, 1}) };

	while (System::Update())
	{
		camera.update(2.0);
		Graphics3D::SetCameraTransform(camera);
		const Mat4x4 billboardMat = camera.getInvView();

		// 3D 描画
		{
			const ScopedRenderTarget3D target{ renderTexture.clear(backgroundColor) };
			Plane{ 64 }.draw(uvChecker);
			Box{ -8,2,0,4 }.draw(ColorF{ 0.8, 0.6, 0.4 }.removeSRGBCurve());
			Sphere{ 0,2,0,2 }.draw(ColorF{ 0.4, 0.8, 0.6 }.removeSRGBCurve());
			Cylinder{ 8, 2, 0, 2, 4 }.draw(ColorF{ 0.6, 0.4, 0.8 }.removeSRGBCurve());

			billboard.draw(camera.billboard(Vec3{ -8, 4, -4 }, 1), uvChecker);
			billboard.draw(camera.billboard(Vec3{ 0, 4, -4 }, 2), uvChecker);
			billboard.draw(camera.billboard(Vec3{ 8, 4, -4 }, 4), uvChecker);

			wideBillboard.draw(camera.billboard(Vec3{ -8, 4, 4 }, { 2, 1 }), uvChecker);
			wideBillboard.draw(camera.billboard(Vec3{ 0, 4, 4 }, { 4, 2 }), uvChecker);
			wideBillboard.draw(camera.billboard(Vec3{ 8, 4, 4 }, { 8, 4 }), uvChecker);
		}

		// 3D シーンを 2D シーンに描画
		{
			Graphics3D::Flush();
			renderTexture.resolve();
			Shader::LinearToScreen(renderTexture);
		}
	}
}
