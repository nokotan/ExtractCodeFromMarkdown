# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);
	const ColorF backgroundColor = ColorF{ 0.4, 0.6, 0.8 }.removeSRGBCurve();
	const Texture woodTexture{ U"example/texture/wood.jpg", TextureDesc::MippedSRGB };
	MeshData meshDataFront = MeshData::Grid(Vec2{ 20,20 }, 256, 256);
	MeshData meshDataBack = MeshData::Grid(Vec2{ 20,20 }, 256, 256).rotate(Quaternion::RotateX(180_deg));
	DynamicMesh meshFront{ meshDataFront }, meshBack{ meshDataBack };
	const PixelShader ps = HLSL{ U"example/shader/hlsl/forward_triplanar.hlsl", U"PS" }
		| GLSL{ U"example/shader/glsl/forward_triplanar.frag", {{ U"PSPerFrame", 0 }, { U"PSPerView", 1 }, { U"PSPerMaterial", 3 }} };
	const MSRenderTexture renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes };
	DebugCamera3D camera{ renderTexture.size(), 30_deg, Vec3{ 16, 12, -24 } };

	TextEditState te;

	while (System::Update())
	{
		if (not te.active)
		{
			camera.update(2.0);
			Graphics3D::SetCameraTransform(camera);
		}

		// 3D
		{
			const ScopedRenderTarget3D target{ renderTexture.clear(backgroundColor) };
			const ScopedCustomShader3D shader{ ps };
			meshFront.draw(woodTexture);
			meshBack.draw(woodTexture);
		}

		// RenderTexture を 2D シーンに描画
		{
			Graphics3D::Flush();
			renderTexture.resolve();
			Shader::LinearToScreen(renderTexture);
		}

		if (SimpleGUI::TextBox(te, Vec2{ 20,20 }, 1240))
		{
			// 数式パーサ
			MathParser parser{ (te.text ? te.text : U"0") };

			// 変数 x, y を設定
			double x = 0;
			double z = 0;
			parser.setVaribale(U"x", &x);
			parser.setVaribale(U"y", &z);

			for (auto& vertex : meshDataFront.vertices)
			{
				x = vertex.pos.x;
				z = vertex.pos.z;

				if (auto y = parser.evalOpt())
				{
					vertex.pos.y = static_cast<float>(*y);
				}
				else
				{
					// 式が不正な場合は終了
					break;
				}
			}

			for (auto& vertex : meshDataBack.vertices)
			{
				x = vertex.pos.x;
				z = vertex.pos.z;

				if (auto y = parser.evalOpt())
				{
					vertex.pos.y = static_cast<float>(*y);
				}
				else
				{
					// 式が不正な場合は終了
					break;
				}
			}

			// 法線を計算
			meshDataFront.computeNormals();
			meshDataBack.computeNormals();

			// DynamicTexture を更新
			meshFront.fill(meshDataFront);
			meshBack.fill(meshDataBack);
		}
	}
}
