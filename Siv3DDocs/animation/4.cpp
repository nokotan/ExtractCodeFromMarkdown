# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(Palette::White);

	double x = 0.0;

	while (System::Update())
	{
		// 毎フレーム 3px 移動（時間ベースではないので不適切！）
		x += 3;

		Circle{ x, 300, 50 }.draw(ColorF{ 0.25 });
	}
}
