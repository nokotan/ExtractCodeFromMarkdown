# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	bool checked0 = false;
	bool checked1 = true;
	bool checked2 = false;
	HSV color = Palette::Orange;

	while (System::Update())
	{
		SimpleGUI::Headline(U"Checkbox", Vec2{ 100, 60 });
		SimpleGUI::CheckBox(checked0, U"Label0", Vec2{ 100, 100 }, 160);
		SimpleGUI::CheckBox(checked1, U"Label1", Vec2{ 100, 140 }, 160);
		SimpleGUI::CheckBox(checked2, U"Label2", Vec2{ 100, 180 }, 160);

		SimpleGUI::Headline(U"ColorPicker", Vec2{ 300, 60 }, 160, false);
		SimpleGUI::ColorPicker(color, Vec2{ 300, 100 }, false);
	}
}
