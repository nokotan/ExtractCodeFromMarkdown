# include <Siv3D.hpp>

void Main()
{
	const Font font{ 50, Typeface::Bold };
	const String text = U"The quick brown fox\njumps over the lazy dog.";

	while (System::Update())
	{
		const double t = Scene::Time();
		constexpr Vec2 basePos{ 20, 20 };
		Vec2 penPos{ basePos };

		// 文字単位で描画を制御するためのループ。index には何番目であるかが格納される
		for (auto [index, glyph] : Indexed(font.getGlyphs(text)))
		{
			if (glyph.codePoint == U'\n')
			{
				penPos.x = basePos.x;
				penPos.y += font.height();
				continue;
			}

			const double offsetY = Math::Sin(index * 45_deg + t * 180_deg) * 10;

			glyph.texture.draw(penPos + glyph.getOffset() + Vec2{ 0, offsetY });

			penPos.x += glyph.xAdvance;
		}
	}
}
