# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(Palette::White);

	double t = 0.0;

	while (System::Update())
	{
		// 経過時間を加算
		t += Scene::DeltaTime();

		Circle{ Scene::Center(), (t * 50) }.draw(ColorF{ 0.25 });
	}
}
