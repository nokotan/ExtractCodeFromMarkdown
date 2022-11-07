# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(Palette::White);

	while (System::Update())
	{
		const double t = Scene::Time();

		for (auto i : step(9))
		{
			Circle{ (i * 100), (t * 100), 20 }.draw(ColorF{ 0.25 });
		}
	}
}
