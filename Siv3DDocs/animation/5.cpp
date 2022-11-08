# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(Palette::White);

	double x = 0.0;

	while (System::Update())
	{
		// 毎秒 180px 移動
		x += (Scene::DeltaTime() * 180);

		Circle{ x, 300, 50 }.draw(ColorF{ 0.25 });
	}
}
