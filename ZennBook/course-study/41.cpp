# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	ColorF color1{ 1.0 };
	ColorF color2{ 1.0, 0.5, 0.0 };
	ColorF color3{ 0.2, 0.6, 0.9 };

	double value1 = 5.0;
	double value2 = 7.0;
	double value3 = 2.0;
	double value4 = 4.0;

	while (System::Update())
	{
		SimpleGUI::Slider(color1.r, Vec2{ 100, 40 });
		SimpleGUI::Slider(color1.g, Vec2{ 100, 80 });
		SimpleGUI::Slider(color1.b, Vec2{ 100, 120 });
		Circle{ 50, 100, 30 }.draw(color1);

		SimpleGUI::Slider(U"Red", color2.r, Vec2{ 100, 200 });
		SimpleGUI::Slider(U"Green", color2.g, Vec2{ 100, 240 });
		SimpleGUI::Slider(U"Blue", color2.b, Vec2{ 100, 280 });
		Circle{ 50, 260, 30 }.draw(color2);

		// スライダーの値を表示、ラベルの幅 100px, スライダーの幅 200px
		SimpleGUI::Slider(U"R {:.2f}"_fmt(color3.r), color3.r, Vec2{ 100, 360 }, 100, 200);
		SimpleGUI::Slider(U"G {:.2f}"_fmt(color3.g), color3.g, Vec2{ 100, 400 }, 100, 200);
		SimpleGUI::Slider(U"B {:.2f}"_fmt(color3.b), color3.b, Vec2{ 100, 440 }, 100, 200);
		Circle{ 50, 420, 30 }.draw(color3);

		// 値の範囲が 0.0～10.0
		SimpleGUI::Slider(U"{:.2f}"_fmt(value1), value1, 0.0, 10.0, Vec2{ 500, 40 }, 60, 150);

		// スライダーを無効化
		SimpleGUI::Slider(U"{:.2f}"_fmt(value2), value2, 0.0, 10.0, Vec2{ 500, 100 }, 60, 150, false);

		// 縦のスライダー
		SimpleGUI::VerticalSlider(value3, 0.0, 10.0, Vec2{ 500, 160 }, 200);
		SimpleGUI::VerticalSlider(value4, 0.0, 10.0, Vec2{ 560, 160 }, 200, false);
	}
}
