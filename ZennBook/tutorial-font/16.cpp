# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	const int32 baseSize = 40;
	const Font fontSDF{ FontMethod::SDF, baseSize, Typeface::Bold };
	const Font fontMSDF{ FontMethod::MSDF, baseSize, Typeface::Bold };
	const String text = U"Hello, Siv3D!";

	const int32 bufferThickness = 3;
	fontSDF.setBufferThickness(bufferThickness);
	fontMSDF.setBufferThickness(bufferThickness);

	while (System::Update())
	{
		const Vec2 shadowOffset{ 2, 2 };
		const ColorF shadowColor{ 0.0, 0.5 };
		const double fontSize = 120;

		// SDF 方式
		fontSDF(text).draw(TextStyle::Shadow(shadowOffset, shadowColor), 20, 20);
		fontSDF(text).draw(TextStyle::Shadow(shadowOffset, shadowColor), fontSize, 20, 60);

		// MSDF 方式
		fontMSDF(text).draw(TextStyle::Shadow(shadowOffset, shadowColor), 20, 220);
		fontMSDF(text).draw(TextStyle::Shadow(shadowOffset, shadowColor), fontSize, 20, 260);
	}
}
