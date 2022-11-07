# include <Siv3D.hpp>

void Main()
{
	const Font font{ 50, Typeface::Regular };

	// ボールド
	const Font fontBold{ 50, Typeface::Regular, FontStyle::Bold };

	// イタリック
	const Font fontItalic{ 50, Typeface::Regular, FontStyle::Italic };

	// ボールド・イタリック
	const Font fontBoldItalic{ 50, Typeface::Regular, FontStyle::BoldItalic };

	const String text = U"Hello, Siv3D! こんにちは。";

	while (System::Update())
	{
		font(text).draw(20, 20);

		fontBold(text).draw(20, 70);

		fontItalic(text).draw(20, 120);

		fontBoldItalic(text).draw(20, 170);
	}
}
