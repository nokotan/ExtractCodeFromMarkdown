# include <Siv3D.hpp>

// 渦巻き効果のピクセルシェーダ用の
// 定数バッファ (PS_1)
struct Swirl
{
	// 回転
	float angle;
};

void Main()
{
	// ゲームの描画用のレンダーテクスチャ
	const MSRenderTexture renderTexture{ Scene::Size() };

	// グレースケール化するピクセルシェーダ
	const PixelShader psGrayscale = HLSL{ U"example/shader/hlsl/grayscale.hlsl", U"PS" }
		| GLSL{ U"example/shader/glsl/grayscale.frag", {{U"PSConstants2D", 0}} };

	if (not psGrayscale)
	{
		throw Error{ U"Failed to load a shader file" };
	}

	// 渦巻き効果のピクセルシェーダ
	const PixelShader psSwirl = HLSL{ U"example/shader/hlsl/swirl.hlsl", U"PS" }
		| GLSL{ U"example/shader/glsl/swirl.frag", {{U"PSConstants2D", 0}, {U"Swirl", 1}} };

	if (not psSwirl)
	{
		throw Error{ U"Failed to load a shader file" };
	}

	// 渦巻き効果のピクセルシェーダ用の定数バッファ
	ConstantBuffer<Swirl> cb;

	// ガウスぼかしの中間で使うレンダーテクスチャ
	const RenderTexture gaussianA1{ renderTexture.size() }, gaussianB1{ renderTexture.size() };
	const RenderTexture gaussianA4{ renderTexture.size() / 4 }, gaussianB4{ renderTexture.size() / 4 };
	const RenderTexture gaussianA8{ renderTexture.size() / 8 }, gaussianB8{ renderTexture.size() / 8 };

	// ゲーム画面に適用するエフェクト
	size_t effectIndex = 0;

	// 背景色
	constexpr ColorF backgroundColor{ 0.3, 0.4, 0.5 };

	// ブロックのサイズ
	constexpr Size brickSize{ 40, 20 };

	// ボールの速さ
	constexpr double speed = 480.0;

	// ボールの速度
	Vec2 ballVelocity{ 0, -speed };

	// ボール
	Circle ball{ 400, 400, 8 };

	// ブロックの配列
	Array<Rect> bricks;

	// 横 (Scene::Width() / blockSize.x) 個、縦 5 個のブロックを配列に追加する
	for (auto p : step(Size{ (Scene::Width() / brickSize.x), 5 }))
	{
		bricks << Rect{ (p.x * brickSize.x), (60 + p.y * brickSize.y), brickSize };
	}

	// 自動プレイ用のパラメータ
	double paddleCenter = 400;
	double randomOffset = 0.0;

	while (System::Update())
	{
		// 自動プレイ
		paddleCenter = Math::Damp(paddleCenter, ball.x + ballVelocity.x * 1.2 + randomOffset, 0.9, Scene::DeltaTime());

		// パドル
		const RectF paddle{ Arg::center(paddleCenter, 500), 120, 10 };

		// ボールを移動
		ball.moveBy(ballVelocity * Scene::DeltaTime());

		// ブロックを順にチェック
		for (auto it = bricks.begin(); it != bricks.end(); ++it)
		{
			// ブロックとボールが交差していたら
			if (it->intersects(ball))
			{
				// ボールの向きを反転する
				(it->bottom().intersects(ball) || it->top().intersects(ball)
					? ballVelocity.y : ballVelocity.x) *= -1;

				// ブロックを配列から削除（イテレータが無効になるので注意）
				bricks.erase(it);

				// これ以上チェックしない
				break;
			}
		}

		// 天井にぶつかったらはね返る
		if (ball.y < 0 && ballVelocity.y < 0)
		{
			ballVelocity.y *= -1;
		}

		// 左右の壁にぶつかったらはね返る
		if ((ball.x < 0 && ballVelocity.x < 0)
			|| (Scene::Width() < ball.x && 0 < ballVelocity.x))
		{
			ballVelocity.x *= -1;
		}

		// パドルにあたったらはね返る
		if (0 < ballVelocity.y && paddle.intersects(ball))
		{
			// パドルの中心からの距離に応じてはね返る方向を変える
			ballVelocity = Vec2{ (ball.x - paddle.center().x) * 10, -ballVelocity.y }.setLength(speed);
			randomOffset = Random(-40, 40);
		}

		// レンダーテクスチャをクリア
		renderTexture.clear(backgroundColor);
		{
			// レンダーターゲットを renderTexture に設定
			const ScopedRenderTarget2D target{ renderTexture };

			for (auto y : Range(1, 5))
			{
				Line{ 0, y * 100, 800, y * 100 }.draw(1, Palette::Gray);
			}

			for (auto x : Range(1, 7))
			{
				Line{ x * 100, 0, x * 100, 600 }.draw(1, Palette::Gray);
			}

			// すべてのブロックを描画する
			for (const auto& brick : bricks)
			{
				brick.stretched(-1).draw(HSV{ brick.y - 40 });
			}

			// ボールを描く
			ball.draw();

			// パドルを描く
			paddle.draw();
		}

		// resolve のために描画を完了させる
		Graphics2D::Flush();

		// マルチサンプル・テクスチャを resolve
		renderTexture.resolve();

		if (effectIndex == 0) // ゲーム画面をそのまま描画
		{
			renderTexture.draw();
		}
		else if (effectIndex == 1) // ゲーム画面をグレースケール化して描画
		{
			// グレースケール化するピクセルシェーダを開始
			const ScopedCustomShader2D shader{ psGrayscale };
			renderTexture.draw();
		}
		else if (effectIndex == 2) // ゲーム画面を渦巻き効果で描画
		{
			cb->angle = static_cast<float>(Math::Sin(Scene::Time()) * 240_deg);

			// 定数バッファを設定
			Graphics2D::SetPSConstantBuffer(1, cb);

			// 渦巻き効果のシェーダを開始
			const ScopedCustomShader2D shader{ psSwirl };
			renderTexture.draw();
		}
		else if (effectIndex == 3) // ゲーム画面をガウスぼかしで描画
		{
			// [オリジナル]->[ガウスぼかし]->[1/4サイズ]->[ガウスぼかし]
			Shader::GaussianBlur(renderTexture, gaussianB1, gaussianA1);
			Shader::Downsample(gaussianA1, gaussianA4);
			Shader::GaussianBlur(gaussianA4, gaussianB4, gaussianA4);
			Shader::Downsample(gaussianA4, gaussianA8);
			Shader::GaussianBlur(gaussianA8, gaussianB8, gaussianA8);

			gaussianA8.scaled(8).draw();
		}

		// エフェクトの種類の選択
		SimpleGUI::RadioButtons(effectIndex, { U"Default", U"Grayscale", U"Swirl", U"GaussianBlur" }, Vec2{ 10, 10 });
	}
}
