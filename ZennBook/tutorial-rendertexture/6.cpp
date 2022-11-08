# include <Siv3D.hpp>

void DrawScene()
{
	Circle{ 680, 40, 20 }.draw();
	Rect{ Arg::center(680, 110), 30 }.draw();
	Triangle{ 680, 180, 40 }.draw();

	Circle{ 740, 40, 20 }.draw(HSV{ 0 });
	Rect{ Arg::center(740, 110), 30 }.draw(HSV{ 120 });
	Triangle{ 740, 180, 40 }.draw(HSV{ 240 });

	Circle{ 50, 200, 300 }.drawFrame(4);
	Circle{ 550, 450, 200 }.drawFrame(4);

	TextureAsset(U"light").drawAt(Scene::Center());

	for (auto i : step(12))
	{
		const double angle = (i * 30_deg + Scene::Time() * 5_deg);
		const Vec2 pos = OffsetCircular{ Scene::Center(), 200, angle };
		Circle{ pos, 8 }.draw(HSV{ i * 30 });
	}
}

void Main()
{
	TextureAsset::Register(U"light", U"💡"_emoji);

	constexpr Size sceneSize{ 800, 600 };
	const RenderTexture gaussianA1{ sceneSize }, gaussianB1{ sceneSize };
	const RenderTexture gaussianA4{ sceneSize / 4 }, gaussianB4{ sceneSize / 4 };
	const RenderTexture gaussianA8{ sceneSize / 8 }, gaussianB8{ sceneSize / 8 };

	bool lightBloom = true;

	while (System::Update())
	{
		// 通常のシーン描画
		DrawScene();

		{
			// ガウスぼかし用テクスチャにもう一度シーンを描く
			{
				const ScopedRenderTarget2D target{ gaussianA1.clear(ColorF{ 0.0 }) };
				const ScopedRenderStates2D blend{ BlendState::Additive };
				DrawScene();
			}

			// オリジナルサイズのガウスぼかし (A1)
			// A1 を 1/4 サイズにしてガウスぼかし (A4)
			// A4 を 1/2 サイズにしてガウスぼかし (A8)
			Shader::GaussianBlur(gaussianA1, gaussianB1, gaussianA1);
			Shader::Downsample(gaussianA1, gaussianA4);
			Shader::GaussianBlur(gaussianA4, gaussianB4, gaussianA4);
			Shader::Downsample(gaussianA4, gaussianA8);
			Shader::GaussianBlur(gaussianA8, gaussianB8, gaussianA8);
		}

		if (lightBloom)
		{
			const ScopedRenderStates2D blend{ BlendState::Additive };
			gaussianA1.resized(sceneSize).draw(ColorF{ 0.1 });
			gaussianA4.resized(sceneSize).draw(ColorF{ 0.4 });
			gaussianA8.resized(sceneSize).draw(ColorF{ 0.8 });
		}

		SimpleGUI::CheckBox(lightBloom, U"lightBloom", Vec2{ 20,20 });
	}
}
