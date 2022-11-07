# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		// 中心が黄色、外周が黒
		Circle{ Scene::Center(), 400 }.draw(Palette::Yellow, Palette::Black);
	}
}
