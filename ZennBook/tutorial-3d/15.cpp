# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);
	const ColorF backgroundColor = ColorF{ 0.4, 0.6, 0.8 }.removeSRGBCurve();
	const Texture uvChecker{ U"example/texture/uv.png", TextureDesc::MippedSRGB };
	const Texture earthTexture{ U"example/texture/earth.jpg", TextureDesc::MippedSRGB };
	const MSRenderTexture renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes };
	DebugCamera3D camera{ renderTexture.size(), 30_deg, Vec3{ 10, 16, -32 } };

	const Mesh plane{ MeshData::TwoSidedPlane(4) };
	const Mesh torus{ MeshData::Torus(1.0, 0.2, 32u, 24u) };

	while (System::Update())
	{
		const double t = Scene::Time();

		camera.update(2.0);
		Graphics3D::SetCameraTransform(camera);

		// 3D 描画
		{
			const ScopedRenderTarget3D target{ renderTexture.clear(backgroundColor) };

			const Transformer3D transformer{ Mat4x4::RotateZ(t * 20_deg) };

			plane.draw(Vec3{ -8, 0, 0 }, Quaternion::RotateX(t * -20_deg), uvChecker);

			{
				const Transformer3D transform2{ Mat4x4::RotateY(t * -40_deg) };
				Sphere{3}.draw(earthTexture);
			}

			torus.draw(Mat4x4::RotateX(t * 90_deg).translated(8, 0, 0));
		}

		// 3D シーンを 2D シーンに描画
		{
			Graphics3D::Flush();
			renderTexture.resolve();
			Shader::LinearToScreen(renderTexture);
		}
	}
}
