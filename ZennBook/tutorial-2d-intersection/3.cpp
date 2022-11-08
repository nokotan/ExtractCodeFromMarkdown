# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(Palette::White);

	const Circle circle{ Scene::Center(), 100 };

	while (System::Update())
	{
		// 円が押されていれば水色、そうでなければ灰色
		circle.draw(circle.leftPressed() ? Palette::Skyblue : Palette::Gray);
	}
}
