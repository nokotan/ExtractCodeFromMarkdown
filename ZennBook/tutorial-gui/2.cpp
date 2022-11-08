# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	bool checked0 = false;
	bool checked1 = true;
	bool checked2 = false;
	bool checked3 = false;
	bool checked4 = false;
	bool checked5 = false;

	while (System::Update())
	{
		SimpleGUI::CheckBox(checked0, U"Label0", Vec2{ 100, 40 });
		SimpleGUI::CheckBox(checked1, U"Label1", Vec2{ 100, 80 });
		SimpleGUI::CheckBox(checked2, U"Label2", Vec2{ 100, 120 });

		// 幅 200px
		SimpleGUI::CheckBox(checked3, U"Label3", Vec2{ 100, 180 }, 200 );

		// 無効化
		SimpleGUI::CheckBox(checked4, U"Label4", Vec2{ 100, 220 }, 200, false);

		// 幅はテキストに合わせる
		SimpleGUI::CheckBox(checked5, U"Label5", Vec2{ 100, 260 }, unspecified, false);
	}
}
