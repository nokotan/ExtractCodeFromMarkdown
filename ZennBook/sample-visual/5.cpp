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

	for (auto i : step(12))
	{
		const double angle = (i * 30_deg + Scene::Time() * 5_deg);
		const Vec2 pos = OffsetCircular{ Scene::Center(), 200, angle };
		Circle{ pos, 8 }.draw(HSV{ i * 30 });
	}
}

void Main()
{
	constexpr Size sceneSize{ 800, 600 };
	RenderTexture gaussianA1{ sceneSize }, gaussianB1{ sceneSize };
	RenderTexture gaussianA4{ sceneSize / 4 }, gaussianB4{ sceneSize / 4 };
	RenderTexture gaussianA8{ sceneSize / 8 }, gaussianB8{ sceneSize / 8 };

	double a1 = 0.0, a4 = 0.0, a8 = 0.0;

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

		{
			const ScopedRenderStates2D blend{ BlendState::Additive };

			if (a1)
			{
				gaussianA1.resized(sceneSize).draw(ColorF{ a1 });
			}

			if (a4)
			{
				gaussianA4.resized(sceneSize).draw(ColorF{ a4 });
			}

			if (a8)
			{
				gaussianA8.resized(sceneSize).draw(ColorF{ a8 });
			}
		}

		SimpleGUI::Slider(U"a1: {:.1f}"_fmt(a1), a1, 0.0, 4.0, Vec2{ 20, 20 });
		SimpleGUI::Slider(U"a4: {:.1f}"_fmt(a4), a4, 0.0, 4.0, Vec2{ 20, 60 });
		SimpleGUI::Slider(U"a8: {:.1f}"_fmt(a8), a8, 0.0, 4.0, Vec2{ 20, 100 });

		if (SimpleGUI::Button(U"0, 0, 0", Vec2{ 20, 140 }))
		{
			a1 = a4 = a8 = 0.0;
		}

		if (SimpleGUI::Button(U"0, 0, 1", Vec2{ 20, 180 }))
		{
			a1= a4 = 0.0;
			a8 = 1.0;
		}

		if (SimpleGUI::Button(U"0, 1, 1", Vec2{ 20, 220 }))
		{
			a1 = 0.0;
			a8 = a4 = 1.0;
		}

		if (SimpleGUI::Button(U"1, 1, 1", Vec2{ 20, 260 }))
		{
			a1 = a4 = a8 = 1.0;
		}
	}
}
