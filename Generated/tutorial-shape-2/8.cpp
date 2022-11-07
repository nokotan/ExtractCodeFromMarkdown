# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(Palette::White);

	while (System::Update())
	{
		const double t = Scene::Time();

		for (auto i : step(6))
		{
			const double width = Max(t - i, 0.0) * 100.0;

			RectF{ 0, (i * 100), width, 100 }.draw(ColorF{ 0.8 - i * 0.1 });
		}
	}
}
