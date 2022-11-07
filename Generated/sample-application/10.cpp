# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.5, 0.7, 0.6 });

	const Font font{ 50, Typeface::Bold };
	const Vec2 center = Scene::Center();

	while (System::Update())
	{
		Circle{ center, 230 }.draw().drawFrame(20, ColorF{ 0.8 });

		// 数字
		for (auto i : Range(1, 12))
		{
			const Vec2 pos = OffsetCircular{ center, 170, (i * 30_deg ) };
			font(i).drawAt(pos, ColorF{ 0.25 });
		}

		for (auto i : Range(0, 59))
		{
			const Vec2 pos = OffsetCircular{ center, 210, i * 6_deg };
			Circle{ pos, (i % 5 ? 3 : 6) }.draw(ColorF{ 0.25 });
		}

		// 現在時刻を取得
		const DateTime time = DateTime::Now();

		// 時針
		const double hour = ((time.hour + time.minute / 60.0) * 30_deg);
		Line{ center, Arg::direction = Circular(110, hour) }
			.draw(LineStyle::RoundCap, 18, ColorF{ 0.1 });

		// 分針
			const double minute = ((time.minute + time.second / 60.0) * 6_deg);
		Line{ center, Arg::direction = Circular(190, minute) }
			.draw(LineStyle::RoundCap, 8, ColorF{ 0.1 });

		// 秒針
		const double second = (time.second * 6_deg);
		Line{ center, Arg::direction = Circular(190, second) }
			.stretched(40, 0)
			.draw(3, ColorF{ 0.1 });
	}
}
