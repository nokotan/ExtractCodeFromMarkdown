# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(Palette::White);

	double r = 0.0;

	while (System::Update())
	{
		// もし左ボタンが押されていたら
		if (MouseL.pressed())
		{
			r += (Scene::DeltaTime() * 100.0);
		}

		Circle{ Scene::Center(), r }.draw(ColorF{ 0.25 });
	}
}
