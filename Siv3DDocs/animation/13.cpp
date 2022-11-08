# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(Palette::White);

	// 2.0 秒かけて 0.0 から 1.0 になる速度で増加し
	// 0.5 秒かけて 1.0 から 0.0 になる速度で減少するトランジション
	Transition transition{ 2.0s, 0.5s };

	while (System::Update())
	{
		// マウスの左ボタンが押されていたら増加、押されていなかったら減少
		transition.update(MouseL.pressed());

		const double t = transition.value();

		Circle{ Scene::Center(), (t * 200) }.draw(ColorF{ 0.25 });
	}
}
