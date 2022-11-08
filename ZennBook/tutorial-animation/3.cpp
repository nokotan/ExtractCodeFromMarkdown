# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(Palette::White);

	while (System::Update())
	{
		const double t = Scene::Time();

		for (auto i : step(6))
		{
			// 円座標系における角度座標
			// 60° ごとに配置し、毎秒 30° の速さで回転する
			const double theta = (i * 60_deg + t * 30_deg);

			const Vec2 pos = OffsetCircular{ Scene::Center(), 200, theta };

			Circle{ pos, 20 }.draw(ColorF{ 0.25 });
		}
	}
}
