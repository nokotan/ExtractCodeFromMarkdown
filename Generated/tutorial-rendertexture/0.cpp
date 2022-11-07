# include <Siv3D.hpp>

void Main()
{
	const Texture emoji{ U"🐈"_emoji };

	// レンダーテクスチャ
	const RenderTexture renderTexture{ 200, 200, Palette::White };

	while (System::Update())
	{
		// レンダーテクスチャを白色でクリア
		renderTexture.clear(Palette::White);

		{
			// レンダーターゲットを renderTexture に変更
			const ScopedRenderTarget2D target{ renderTexture };

			Circle{ 200, 200, 160 }.draw(ColorF{ 0.8, 0.9, 1.0 });

			emoji.rotated(Scene::Time() * 30_deg).drawAt(100, 100);
		} // ここで target のスコープが終了し、レンダーターゲットがシーンに戻る

		// レンダーテクスチャを描画する
		renderTexture.draw(0, 0);
		renderTexture.draw(200, 200);
		renderTexture.draw(400, 400);
	}
}
