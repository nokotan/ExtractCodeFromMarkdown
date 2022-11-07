# include <Siv3D.hpp>

struct RingEffect : IEffect
{
	Vec2 m_pos;

	explicit RingEffect(const Vec2& pos)
		: m_pos{ pos } {}

	bool update(double t) override
	{
		Circle{ m_pos, (t * 100) }.drawFrame(4);

		return (t < 1.0);
	}
};

void Main()
{
	Effect effect;

	// 出現間隔（秒）
	constexpr double spawnTime = 0.15;

	// 蓄積された時間（秒）
	double accumulator = 0.0;

	while (System::Update())
	{
		ClearPrint();
		Print << U"Active effects: {}"_fmt(effect.num_effects());
		Print << U"speed: {}"_fmt(effect.getSpeed());

		if (not effect.isPaused())
		{
			accumulator += (Scene::DeltaTime() * effect.getSpeed());
		}

		// 蓄積時間が出現間隔を超えたら
		if (spawnTime <= accumulator)
		{
			accumulator -= spawnTime;

			effect.add<RingEffect>(Cursor::Pos());
		}

		effect.update();

		if (effect.isPaused())
		{
			if (SimpleGUI::Button(U"Resume", Vec2{ 600, 20 }, 100))
			{
				// エフェクトの更新を再開
				effect.resume();
			}
		}
		else
		{
			if (SimpleGUI::Button(U"Pause", Vec2{ 600, 20 }, 100))
			{
				// エフェクトの更新を一時停止
				effect.pause();
			}
		}

		if (SimpleGUI::Button(U"x2.0", Vec2{ 600, 60 }, 100))
		{
			// 2.0 倍速に
			effect.setSpeed(2.0);
		}

		if (SimpleGUI::Button(U"x1.0", Vec2{ 600, 100 }, 100))
		{
			// 1.0 倍速に
			effect.setSpeed(1.0);
		}

		if (SimpleGUI::Button(U"x0.5", Vec2{ 600, 140 }, 100))
		{
			// 0.5 倍速に
			effect.setSpeed(0.5);
		}

		if (SimpleGUI::Button(U"Clear", Vec2{ 600, 180 }, 100))
		{
			// 発生中のエフェクトをすべて消去
			effect.clear();
		}
	}
}
