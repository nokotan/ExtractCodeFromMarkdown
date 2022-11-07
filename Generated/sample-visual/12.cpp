# include <Siv3D.hpp>

// ボール用のパーティクルクラス
class BallParticleSystem
{
public:

	BallParticleSystem(const Vec2& pos, const Vec2& force)
		: m_system{ pos, force }
		, m_texture{ U"example/particle.png", TextureDesc::Mipped }
	{
		m_system.setTexture(m_texture);

		// パラメータ
		ParticleSystem2DParameters parameters;
		parameters.rate = 300.0;
		parameters.startSpeed = 50.0;
		parameters.startColor = HSV{ 10.0, 0.8, 0.25 };
		parameters.startSize = 60.0;
		parameters.blendState = BlendState::Additive;
		m_system.setParameters(parameters);

		// エミッター
		CircleEmitter2D circleEmitter;
		circleEmitter.r = 12.0;
		m_system.setEmitter(circleEmitter);

		m_system.prewarm();
	}

	void setPos(const Vec2& pos)
	{
		m_system.setPosition(pos);
	}

	void update()
	{
		m_system.update();
	}

	void draw() const
	{
		m_system.draw();
	}

private:

	// 2D パーティクルシステム
	ParticleSystem2D m_system;

	// パーティクル用のテクスチャ
	Texture m_texture;
};

void Main()
{
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

	// ボール用のパーティクルクラス
	BallParticleSystem particleSystem{ ball.center, Vec2{ 0.0, -120 } };

	while (System::Update())
	{
		// パドル
		const Rect paddle{ Arg::center(Cursor::Pos().x, 500), 60, 10 };

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
		}

		// パーティクル更新
		particleSystem.setPos(ball.center);
		particleSystem.update();

		// すべてのブロックを描画する
		for (const auto& brick : bricks)
		{
			brick.stretched(-1).draw(HSV{ brick.y - 40 });
		}

		// ボールを描く
		ball.draw();

		// パドルを描く
		paddle.draw();

		// パーティクル描画
		particleSystem.draw();
	}
}
