# include <Siv3D.hpp>

void Main()
{
	// 基本サイズ
	const int32 baseSize = 40;

	const Font font{ baseSize, Typeface::Bold };
	const Font fontSDF{ FontMethod::SDF, baseSize, Typeface::Bold };
	const Font fontMSDF{ FontMethod::MSDF, baseSize, Typeface::Bold };
	const String text = U"Hello, Siv3D!";

	while (System::Update())
	{
		// 文字のサイズ（指定しない場合は基本サイズで描かれる）
		const double fontSize = 120;

		// 通常（ビットマップ方式）
		font(text).draw(20, 20);
		font(text).draw(fontSize, 20, 50);

		// SDF 方式
		fontSDF(text).draw(20, 220);
		fontSDF(text).draw(fontSize, 20, 250);

		// MSDF 方式
		fontMSDF(text).draw(20, 420);
		fontMSDF(text).draw(fontSize, 20, 450);
	}
}
