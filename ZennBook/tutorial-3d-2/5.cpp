# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);
	const ColorF backgroundColor = ColorF{ 0.4, 0.6, 0.8 }.removeSRGBCurve();
	const Texture uvChecker{ U"example/texture/uv.png", TextureDesc::MippedSRGB };
	const MSRenderTexture renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes };
	DebugCamera3D camera{ renderTexture.size(), 30_deg, Vec3{ 10, 16, -32 } };

	const Mesh mesh{ MeshData::TwoSidedPlane(Vec2{16, 9}) };

	// ループする場合は Loop::Yes, ループしない場合は Loop::No, (VideoTexture に Mipped は効かない)
	const VideoTexture videoTexture{ U"example/video/river.mp4", Loop::Yes, TextureDesc::MippedSRGB };

	while (System::Update())
	{
		// 動画の時間を進める (デフォルトでは Scece::DeltaTime() 秒)
		videoTexture.advance();

		camera.update(2.0);
		Graphics3D::SetCameraTransform(camera);

		// 3D 描画
		{
			const ScopedRenderTarget3D target{ renderTexture.clear(backgroundColor) };
			Plane{ 64 }.draw(uvChecker);
			mesh.draw(Vec3{ 0, 4.5, 8 }, Quaternion::RotateX(-90_deg), videoTexture);
			Box{ -8,2,0,4 }.draw(videoTexture);
			Sphere{ 0,2,0,2 }.draw(videoTexture);
			Cylinder{ 8, 2, 0, 2, 4 }.draw(videoTexture);
		}

		// 3D シーンを 2D シーンに描画
		{
			Graphics3D::Flush();
			renderTexture.resolve();
			Shader::LinearToScreen(renderTexture);
		}
	}
}
