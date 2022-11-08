# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(Palette::White);

	const Circle circle{ Scene::Center(), 100 };

	while (System::Update())
	{
		if (circle.mouseOver())
		{
			// 円にマウスカーソルが重なっていれば水色
			circle.draw(Palette::Skyblue);
		}
		else
		{
			// 重なっていなければ灰色
			circle.draw(Palette::Gray);
		}
	}
}
