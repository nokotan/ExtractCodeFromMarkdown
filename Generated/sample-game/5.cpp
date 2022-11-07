# include <Siv3D.hpp>

struct Bubble
{
	// バブルの円の半径
	static constexpr int32 CircleR = 30;

	// バブルの円
	Circle circle;

	// バブルのインデックス
	int32 index;

	// 接続済みなら true に
	bool connected = false;

	void draw() const
	{
		if (connected)
		{
			circle.drawShadow(Vec2{ 1, 2 }, 10, 3).draw()
				.drawFrame(2, 0, ColorF{ 0.3, 0.6, 1.0 });
		}
		else
		{
			circle.draw();
		}

		FontAsset(U"Bubble")(index + 1).drawAt(circle.center, ColorF{ 0.25 });
	}
};

// バブルどうしが重なっていないかチェック
bool CheckBubbles(const Array<Bubble>& bubbles)
{
	for (auto i : step(bubbles.size()))
	{
		for (auto k : step(bubbles.size()))
		{
			// 自分どうしとは交差判定しない
			if (i == k)
			{
				continue;
			}

			// 重なっている
			if (bubbles[i].circle.stretched(5).intersects(bubbles[k].circle.stretched(5)))
			{
				return false;
			}
		}
	}

	return true;
}

// 指定した個数のバブルを重ならないように生成
Array<Bubble> MakeBubbles(int32 count)
{
	Array<Bubble> bubbles(count);

	do
	{
		for (auto i : step(count))
		{
			// バブルのインデックス
			bubbles[i].index = i;

			// バブルの円
			bubbles[i].circle.set(RandomVec2(Circle{ Scene::Center(), (Scene::Height() / 2 - Bubble::CircleR) }), Bubble::CircleR);
		}
	} while (not CheckBubbles(bubbles));

	return bubbles;
}

// 指定したレベルにおけるバブルの個数
constexpr int32 GetBubbleCount(int32 level)
{
	return Min(level, 15);
}

// 指定したレベルにおける制限時間（秒）
constexpr Duration GetTime(int32 level)
{
	return Duration{ (level <= 15) ? 8.0 : 8.0 - Min((level - 15) * 0.05, 2.0) };
}

void Main()
{
	Scene::SetBackground(Palette::White);
	FontAsset::Register(U"Bubble", 36, Typeface::Medium);
	Effect effect;

	// 効果音を作成
	const Array<PianoKey> keys = { PianoKey::C5,  PianoKey::D5, PianoKey::E5, PianoKey::F5, PianoKey::G5,
		PianoKey::A5, PianoKey::B5, PianoKey::C6, PianoKey::D6, PianoKey::E6,
		PianoKey::F6, PianoKey::G6, PianoKey::A6, PianoKey::B6, PianoKey::C7 };
	const Array<Audio> sounds = keys.map([](auto k) { return Audio{ GMInstrument::Glockenspiel, k, 0.3s }; });

	// ハイスコア
	int32 highScore = 0;

	// 現在のレベル
	int32 level = 1;

	// 接続数
	int32 connected = 0;

	// 残り時間のタイマー
	Timer timer{ GetTime(level), StartImmediately::Yes };

	// バブル
	Array<Bubble> bubbles = MakeBubbles(GetBubbleCount(level));

	while (System::Update())
	{
		const double delta = Scene::DeltaTime();

		// 制限時間を表す背景
		RectF{ Scene::Size() * Vec2 { 1, timer.progress0_1() } }.draw(HSV{ (level * 30), 0.3, 0.9 });

		for (auto& bubble : bubbles)
		{
			if ((bubble.index == connected)
				&& (not bubble.connected)
				&& bubble.circle.stretched(10).mouseOver())
			{
				// 接続済みに
				bubble.connected = true;

				// 接続数を増やす
				++connected;

				// エフェクトを追加
				effect.add([pos = Cursor::Pos()](double t)
				{
					Circle{ pos, (Bubble::CircleR + t * 200) }.drawFrame(2, 0, ColorF{ 0.2, 0.5, 1.0, (1.0 - t * 2.5) });
					return (t < 0.4);
				});

				// バブルの数字に応じて効果音を鳴らす
				sounds[bubble.index].playOneShot(0.8);
			}

			// バブルを円周に沿って移動
			bubble.circle.center = OffsetCircular{ Scene::Center(), bubble.circle.center }
				.rotate((IsEven(bubble.index) ? 20_deg : -20_deg) * delta);
		}

		// バブルをすべてつなぐか、時間切れになったら
		if (const bool failed = timer.reachedZero();
			(connected == GetBubbleCount(level)) || failed)
		{
			// レベルを更新
			level = (failed ? 1 : ++level);

			// 接続数をリセット
			connected = 0;

			// 制限時間をリセット
			timer = Timer{ GetTime(level), StartImmediately::Yes };

			// バブルを再生成
			bubbles = MakeBubbles(GetBubbleCount(level));

			// ハイスコアを更新
			highScore = Max(highScore, level);

			// タイトルを更新
			Window::SetTitle(U"Level {} (High score: {})"_fmt(level, highScore));
		}

		// バブルをつなぐ線
		for (int32 i = 0; i < (connected - 1); ++i)
		{
			Line{ bubbles[i].circle.center, bubbles[i + 1].circle.center }.draw(3, Palette::Orange);
		}

		// バブルを描画
		for (const auto& bubble : bubbles)
		{
			bubble.draw();
		}

		effect.update();
	}
}
