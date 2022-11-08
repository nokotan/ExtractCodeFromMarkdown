# include <Siv3D.hpp>

void DrawLargeWall()
{
	Box{ 0,4,8,32,8,1 }.draw(ColorF{ 0.8, 0.6, 0.4 }.removeSRGBCurve());
}

void DrawMiddleWall()
{
	Box{ 0,3,6,32,6,1 }.draw(ColorF{ 0.6, 0.4, 0.8, 0.6 }.removeSRGBCurve());
}

void DrawLeftBox(const Texture& emoji)
{
	Box{ -8,2,0,4 }.draw(emoji);
}

void DrawSphere()
{
	Sphere{ 0,2,0,4 }.draw(ColorF{ 0.2, 0.6, 1.0, 0.5 }.removeSRGBCurve());
}

void DrawRightBox(const Texture& emoji)
{
	Box{ 8,2,0,4 }.draw(emoji, ColorF{ 1.0, 0.7 });
}

void Main()
{
	Window::Resize(1280, 720);
	const ColorF backgroundColor = ColorF{ 0.4, 0.6, 0.8 }.removeSRGBCurve();
	const Texture uvChecker{ U"example/texture/uv.png", TextureDesc::MippedSRGB };
	const Texture emoji{ U"🐈"_emoji, TextureDesc::MippedSRGB };
	const MSRenderTexture renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes };
	DebugCamera3D camera{ renderTexture.size(), 30_deg, Vec3{ 10, 16, -32 } };

	size_t index = 0;

	while (System::Update())
	{
		camera.update(2.0);
		Graphics3D::SetCameraTransform(camera);

		if (index == 0)
		{
			const ScopedRenderTarget3D target{ renderTexture.clear(backgroundColor) };
			Plane{ 64 }.draw(uvChecker);
			DrawLargeWall();
			DrawLeftBox(emoji);
			DrawSphere();
			DrawRightBox(emoji);
			DrawMiddleWall();
		}
		else if (index == 1)
		{
			const ScopedRenderTarget3D target{ renderTexture.clear(backgroundColor) };
			Plane{ 64 }.draw(uvChecker);
			DrawLargeWall();
			{
				const ScopedRenderStates3D blend{ BlendState::Default2D };
				DrawLeftBox(emoji);
				DrawSphere();
				DrawRightBox(emoji);
				DrawMiddleWall();
			}
		}
		else if (index == 2)
		{
			const ScopedRenderTarget3D target{ renderTexture.clear(backgroundColor) };
			Plane{ 64 }.draw(uvChecker);
			DrawLargeWall();
			{
				const ScopedRenderStates3D blend{ BlendState::Default2D };
				DrawMiddleWall();

				if (0 < camera.getEyePosition().x)
				{
					DrawLeftBox(emoji);
					DrawSphere();
					DrawRightBox(emoji);
				}
				else
				{
					DrawRightBox(emoji);
					DrawSphere();
					DrawLeftBox(emoji);
				}
			}
		}
		else 
		{
			const ScopedRenderTarget3D target{ renderTexture.clear(backgroundColor) };
			Plane{ 64 }.draw(uvChecker);
			DrawLargeWall();
			{
				const ScopedRenderStates3D blend{ BlendState::OpaqueAlphaToCoverage };
				DrawLeftBox(emoji);
				DrawSphere();
				DrawRightBox(emoji);
				DrawMiddleWall();
			}
		}

		// 3D シーンを 2D シーンに描画
		{
			Graphics3D::Flush();
			renderTexture.resolve();
			Shader::LinearToScreen(renderTexture);
		}

		SimpleGUI::RadioButtons(index,
			{ U"Default",
			  U"BlendState::Default2D",
			  U"BlendState::Default2D + sort by distance",
			  U"BlendState::OpaqueAlphaToCoverage"
			}, Vec2{ 20, 20 });
	}
}
