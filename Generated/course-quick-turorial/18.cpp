# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		// 色相 hue = 経過時間 (秒) * 60
		const double hue = (Scene::Time() * 60);

		Scene::SetBackground(HSV{ hue, 0.6, 1.0 });
	}
}
