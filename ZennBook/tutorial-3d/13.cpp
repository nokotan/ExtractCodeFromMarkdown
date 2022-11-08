# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);
	const ColorF backgroundColor = ColorF{ 0.4, 0.6, 0.8 }.removeSRGBCurve();
	const Texture uvChecker{ U"example/texture/uv.png", TextureDesc::MippedSRGB };
	const MSRenderTexture renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes };
	DebugCamera3D camera{ renderTexture.size(), 30_deg, Vec3{ 10, 16, -32 } };

	const Mesh oneSidedPlane{ MeshData::OneSidedPlane(Vec2{ 6,2 }) };
	const Mesh twoSidedPlane{ MeshData::TwoSidedPlane(Vec2{ 4,3 }) };
	const Mesh box{ MeshData::Box(Vec3{ 6, 2, 2 }) };
	const Mesh sphere8{ MeshData::Sphere(3, 8u) };
	const Mesh sphere24{ MeshData::Sphere(3, 24u) };

	const Mesh subdivSphere2{ MeshData::SubdividedSphere(3, 2u) };
	const Mesh subdivSphere3{ MeshData::SubdividedSphere(3, 3u) };
	const Mesh subdivSphere4{ MeshData::SubdividedSphere(3, 4u) };
	const Mesh disc8{ MeshData::Disc(3, 8u) };
	const Mesh disc16{ MeshData::Disc(3, 16u) };

	const Mesh cylinder6{ MeshData::Cylinder(Vec3{0,0,0}, 3, 4, 6u) };
	const Mesh cylinder24{ MeshData::Cylinder(Vec3{0,0,0}, 3, 4, 24u) };
	const Mesh cone6{ MeshData::Cone(Vec3{0,0,0}, 3, 4, 6u) };
	const Mesh cone24{ MeshData::Cone(Vec3{0,0,0}, 3, 4, 24u) };
	const Mesh pyramid{ MeshData::Pyramid(3.0, 3.0) };

	const Mesh torus{ MeshData::Torus(3.0, 0.6) };
	const Mesh hemisphere{ MeshData::Hemisphere(3.0) };
	const Mesh tetrahedron{ MeshData::Tetrahedron(3.0) };
	const Mesh octahedron{ MeshData::Octahedron(3.0) };
	const Mesh dodecahedron{ MeshData::Dodecahedron(3.0) };

	const Mesh icosahedron{ MeshData::Icosahedron(3.0) };
	const Mesh grid{ MeshData::Grid(Vec2{4.0,2.0}, 10, 5, Vec2{2, 1}) };

	bool wireframe = false;

	while (System::Update())
	{
		camera.update(2.0);
		Graphics3D::SetCameraTransform(camera);

		// 3D 描画
		{
			const ScopedRenderTarget3D target{ renderTexture.clear(backgroundColor) };
			const ScopedRenderStates3D rastetrizer{ (wireframe ? RasterizerState::WireframeCullNone : RasterizerState::Default3D) };

			oneSidedPlane.draw(-16, 0, 16, uvChecker);
			twoSidedPlane.draw(-8, 0, 16, uvChecker);
			box.draw(0, 0, 16, uvChecker);
			sphere8.draw(8, 0, 16, uvChecker);
			sphere24.draw(16, 0, 16, uvChecker);

			subdivSphere2.draw(-16, 0, 8, uvChecker);
			subdivSphere3.draw(-8, 0, 8, uvChecker);
			subdivSphere4.draw(0, 0, 8, uvChecker);
			disc8.draw(8, 0, 8, uvChecker);
			disc16.draw(16, 0, 8, uvChecker);

			cylinder6.draw(-16, 0, 0, uvChecker);
			cylinder24.draw(-8, 0, 0, uvChecker);
			cone6.draw(0, 0, 0, uvChecker);
			cone24.draw(8, 0, 0, uvChecker);
			pyramid.draw(16, 0, 0, uvChecker);

			torus.draw(-16, 0, -8, uvChecker);
			hemisphere.draw(-8, 0, -8, uvChecker);
			tetrahedron.draw(0, 0, -8, uvChecker);
			octahedron.draw(8, 0, -8, uvChecker);
			dodecahedron.draw(16, 0, -8, uvChecker);

			icosahedron.draw(-16, 0, -16, uvChecker);
			grid.draw(-8, 0, -16, uvChecker);
		}

		// 3D シーンを 2D シーンに描画
		{
			Graphics3D::Flush();
			renderTexture.resolve();
			Shader::LinearToScreen(renderTexture);
		}

		SimpleGUI::CheckBox(wireframe, U"wireframe", Vec2{ 20,20 });
	}
}
