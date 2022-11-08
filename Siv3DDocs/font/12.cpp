# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	const Font font{ 25, Typeface::Bold };
	const String text = U"The quick brown fox jumps over the lazy dog.";

	constexpr Rect rect1{ 50, 20, 200, 100 };
	constexpr Rect rect2{ 50, 160, 300, 100 };
	constexpr Rect rect3{ 50, 300, 400, 100 };

	while (System::Update())
	{
		rect1.draw();
		if (not font(text).draw(rect1.stretched(-10), ColorF{ 0.25 }))
		{
			// 文字が省略されたら赤枠
			rect1.drawFrame(0, 5, Palette::Red);
		}

		rect2.draw();
		if (not font(text).draw(rect2.stretched(-10), ColorF{ 0.25 }))
		{
			// 文字が省略されたら赤枠
			rect2.drawFrame(0, 5, Palette::Red);
		}

		rect3.stretched(10).draw();
		if (not font(text).draw(rect3.stretched(-10), ColorF(0.25)))
		{
			// 文字が省略されたら赤枠
			rect3.drawFrame(0, 5, Palette::Red);
		}
	}
}
