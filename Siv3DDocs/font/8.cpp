# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	const Font font{ 32, U"example/font/DotGothic16/DotGothic16-Regular.ttf" };

	const Font fontB{ 32, U"example/font/DotGothic16/DotGothic16-Regular.ttf", FontStyle::Bitmap };

	const String text = U"Hello, Siv3D! こんにちは。";

	while (System::Update())
	{
		font(text).draw(20, 20, Palette::Black);

		fontB(text).draw(20, 60, Palette::Black);
	}
}
