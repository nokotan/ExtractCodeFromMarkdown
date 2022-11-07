# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	// レンダーテクスチャ
	const RenderTexture renderTexture{ 200, 200, Palette::White };

	// マルチサンプル・レンダーテクスチャ
	const MSRenderTexture msRenderTexture{ 200, 200, Palette::White };

	while (System::Update())
	{
		// レンダーテクスチャ
		{
			const ScopedRenderTarget2D target{ renderTexture.clear(Palette::Black) };

			Rect{ Arg::center(100, 100), 80 }
				.rotated(Scene::Time() * 30_deg).draw();
		}

		// マルチサンプル・レンダーテクスチャ
		{
			const ScopedRenderTarget2D target{ msRenderTexture.clear(Palette::Black) };

			Rect{ Arg::center(100, 100), 80 }
				.rotated(Scene::Time() * 30_deg).draw();
		}

		// 2D 描画をフラッシュ
		Graphics2D::Flush();

		// マルチサンプル・テクスチャをリゾルブ
		msRenderTexture.resolve();

		renderTexture.draw(100, 0);
		msRenderTexture.draw(400, 0);
	}
}
