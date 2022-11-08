# include <Siv3D.hpp>

// シーンの名前
enum class State
{
	Title,
	Game,
	Ranking,
};

// 共有するデータ
struct GameData
{
	// 直前のゲームのスコア
	Optional<int32> lastGameScore;

	// ハイスコア
	Array<int32> highScores = { 50, 40, 30, 20, 10 };
};

using App = SceneManager<State, GameData>;

// タイトルシーン
class Title : public App::Scene
{
public:

	Title(const InitData& init)
		: IScene{ init } {}

	void update() override
	{
		m_startTransition.update(m_startButton.mouseOver());
		m_rankingTransition.update(m_rankingButton.mouseOver());
		m_exitTransition.update(m_exitButton.mouseOver());

		if (m_startButton.mouseOver() || m_rankingButton.mouseOver() || m_exitButton.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}

		if (m_startButton.leftClicked())
		{
			// ゲームシーンへ
			changeScene(State::Game);
		}
		else if (m_rankingButton.leftClicked())
		{
			// ランキングシーンへ
			changeScene(State::Ranking);
		}
		else if (m_exitButton.leftClicked())
		{
			// 終了
			System::Exit();
		}
	}

	void draw() const override
	{
		Scene::SetBackground(ColorF{ 0.2, 0.8, 0.4 });

		FontAsset(U"TitleFont")(U"BREAKOUT")
			.drawAt(TextStyle::OutlineShadow(0.2, ColorF{ 0.2, 0.6, 0.2 }, Vec2{ 3, 3 }, ColorF{ 0.0, 0.5 }), 100, Vec2{ 400, 100 });

		m_startButton.draw(ColorF{ 1.0, m_startTransition.value() }).drawFrame(2);
		m_rankingButton.draw(ColorF{ 1.0, m_rankingTransition.value() }).drawFrame(2);
		m_exitButton.draw(ColorF{ 1.0, m_exitTransition.value() }).drawFrame(2);

		FontAsset(U"Menu")(U"PLAY").drawAt(m_startButton.center(), ColorF{ 0.25 });
		FontAsset(U"Menu")(U"RANKING").drawAt(m_rankingButton.center(), ColorF{ 0.25 });
		FontAsset(U"Menu")(U"EXIT").drawAt(m_exitButton.center(), ColorF{ 0.25 });
	}

private:

	Rect m_startButton{ Arg::center = Scene::Center(), 300, 60 };
	Transition m_startTransition{ 0.4s, 0.2s };

	Rect m_rankingButton{ Arg::center = Scene::Center().movedBy(0, 100), 300, 60 };
	Transition m_rankingTransition{ 0.4s, 0.2s };

	Rect m_exitButton{ Arg::center = Scene::Center().movedBy(0, 200), 300, 60 };
	Transition m_exitTransition{ 0.4s, 0.2s };
};

// ゲームシーン
class Game : public App::Scene
{
public:

	Game(const InitData& init)
		: IScene{ init }
	{
		// 横 (Scene::Width() / blockSize.x) 個、縦 5 個のブロックを配列に追加する
		for (auto p : step(Size{ (Scene::Width() / BrickSize.x), 5 }))
		{
			m_bricks << Rect{ (p.x * BrickSize.x), (60 + p.y * BrickSize.y), BrickSize };
		}
	}

	void update() override
	{
		// ボールを移動
		m_ball.moveBy(m_ballVelocity * Scene::DeltaTime());

		// ブロックを順にチェック
		for (auto it = m_bricks.begin(); it != m_bricks.end(); ++it)
		{
			// ブロックとボールが交差していたら
			if (it->intersects(m_ball))
			{
				// ボールの向きを反転する
				(it->bottom().intersects(m_ball) || it->top().intersects(m_ball)
					? m_ballVelocity.y : m_ballVelocity.x) *= -1;

				// ブロックを配列から削除（イテレータが無効になるので注意）
				m_bricks.erase(it);

				AudioAsset(U"Brick").playOneShot(0.5);

				// スコアを加算
				++m_score;

				// これ以上チェックしない
				break;
			}
		}

		// 天井にぶつかったらはね返る
		if (m_ball.y < 0 && m_ballVelocity.y < 0)
		{
			m_ballVelocity.y *= -1;
		}

		// 左右の壁にぶつかったらはね返る
		if ((m_ball.x < 0 && m_ballVelocity.x < 0)
			|| (Scene::Width() < m_ball.x && 0 < m_ballVelocity.x))
		{
			m_ballVelocity.x *= -1;
		}

		// パドルにあたったらはね返る
		if (const Rect paddle = getPaddle();
			(0 < m_ballVelocity.y) && paddle.intersects(m_ball))
		{
			// パドルの中心からの距離に応じてはね返る方向を変える
			m_ballVelocity = Vec2{ (m_ball.x - paddle.center().x) * 10, -m_ballVelocity.y }.setLength(Speed);
		}

		// 画面外に出るか、ブロックが無くなったら
		if ((Scene::Height() < m_ball.y) || m_bricks.isEmpty())
		{
			// ランキング画面へ
			changeScene(State::Ranking);

			getData().lastGameScore = m_score;
		}
	}

	void draw() const override
	{
		Scene::SetBackground(ColorF{ 0.2 });

		// すべてのブロックを描画する
		for (const auto& brick : m_bricks)
		{
			brick.stretched(-1).draw(HSV{ brick.y - 40 });
		}

		// ボールを描く
		m_ball.draw();

		// パドルを描く
		getPaddle().draw();

		FontAsset(U"GameScore")(m_score).draw(10, 10);
	}

private:

	// ブロックのサイズ
	static constexpr Size BrickSize{ 40, 20 };

	// ボールの速さ
	static constexpr double Speed = 480.0;

	// ボールの速度
	Vec2 m_ballVelocity{ 0, -Speed };

	// ボール
	Circle m_ball{ 400, 400, 8 };

	// ブロックの配列
	Array<Rect> m_bricks;

	// 現在のゲームのスコア
	int32 m_score = 0;

	Rect getPaddle() const
	{
		return{ Arg::center(Cursor::Pos().x, 500), 60, 10 };
	}
};

// ランキングシーン
class Ranking : public App::Scene
{
public:

	Ranking(const InitData& init)
		: IScene{ init }
	{
		auto& data = getData();

		if (data.lastGameScore)
		{
			const int32 lastScore = *data.lastGameScore;

			// ランキングを再構成
			data.highScores << lastScore;
			data.highScores.rsort();
			data.highScores.resize(RankingCount);

			// ランクインしていたら m_rank に順位をセット
			for (int32 i = 0; i < RankingCount; ++i)
			{
				if (data.highScores[i] == lastScore)
				{
					m_rank = i;
					break;
				}
			}

			data.lastGameScore.reset();
		}
	}

	void update() override
	{
		if (MouseL.down())
		{
			// タイトルシーンへ
			changeScene(State::Title);
		}
	}

	void draw() const override
	{
		Scene::SetBackground(ColorF{ 0.4, 0.6, 0.9 });

		FontAsset(U"Ranking")(U"RANKING").drawAt(400, 60);

		const auto& data = getData();

		// ランキングを表示
		for (auto i : step(RankingCount))
		{
			const RectF rect{ 100, 120 + i * 80, 600, 80 };

			rect.draw(ColorF{ 1.0, 1.0 - i * 0.2 });

			FontAsset(U"Ranking")(data.highScores[i]).drawAt(rect.center(), ColorF{ 0.25 });

			// ランクインしていたら
			if (i == m_rank)
			{
				rect.stretched(Periodic::Triangle0_1(0.5s) * 10).drawFrame(10, ColorF{ 0.8, 0.6, 0.4 });
			}
		}
	}

private:

	static constexpr int32 RankingCount = 5;

	int32 m_rank = -1;
};

void Main()
{
	FontAsset::Register(U"TitleFont", FontMethod::MSDF, 50, U"example/font/RocknRoll/RocknRollOne-Regular.ttf");
	FontAsset(U"TitleFont").setBufferThickness(4);
	FontAsset::Register(U"Menu", FontMethod::MSDF, 40, Typeface::Medium);
	FontAsset::Register(U"Ranking", 40, Typeface::Heavy);
	FontAsset::Register(U"GameScore", 30, Typeface::Light);
	AudioAsset::Register(U"Brick", GMInstrument::Woodblock, PianoKey::C5, 0.2s, 0.1s);

	App manager;
	manager.add<Title>(State::Title);
	manager.add<Game>(State::Game);
	manager.add<Ranking>(State::Ranking);

	// ゲームシーンから開始したい場合はこのコメントを外す
	//manager.init(State::Game);

	while (System::Update())
	{
		if (not manager.update())
		{
			break;
		}
	}
}
