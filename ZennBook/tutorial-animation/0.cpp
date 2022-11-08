# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(Palette::White);

	while (System::Update())
	{
		const double t = Scene::Time();

		// 円の半径が、時間の経過に伴って大きくなる
		Circle{ Scene::Center(), (t * 50) }.draw(ColorF{ 0.25 });
	}
}
