# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	HSV color0 = Palette::Orange;
	HSV color1 = Palette::Skyblue;

	while (System::Update())
	{
		SimpleGUI::ColorPicker(color0, Vec2{ 100, 100 });
		Rect{ 100, 300, 100 }.draw(color0);

		SimpleGUI::ColorPicker(color1, Vec2{ 300, 100 }, false);
		Rect{ 300, 300, 100 }.draw(color1);
	}
}
