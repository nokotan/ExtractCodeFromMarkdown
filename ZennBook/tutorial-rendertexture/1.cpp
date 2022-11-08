# include <Siv3D.hpp>

void Main()
{
	const Texture emoji{ U"🐈"_emoji };

	const RenderTexture renderTexture{ 200, 200, Palette::White };

	while (System::Update())
	{
		{
			// renderTexture をクリアし、レンダーターゲットを renderTexture に変更
			const ScopedRenderTarget2D target{ renderTexture.clear(Palette::White) };

			Circle{ 200, 200, 160 }.draw(ColorF{ 0.8, 0.9, 1.0 });

			emoji.rotated(Scene::Time() * 30_deg).drawAt(100, 100);
		}

		renderTexture.draw(0, 0);
		renderTexture.draw(200, 200);
		renderTexture.draw(400, 400);
	}
}
