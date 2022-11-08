# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	// MSDF フォント
	const Font font{ FontMethod::MSDF, 50, Typeface::Bold };
	const String text = U"The quick brown fox\njumps over the lazy dog.";

	while (System::Update())
	{
		const double t = Scene::Time();
		constexpr Vec2 basePos{ 20, 20 };
		Vec2 penPos{ basePos };

		{
			// MSDF フォント + 影 + 輪郭描画のための設定
			const ScopedCustomShader2D shader{ Font::GetPixelShader(font.method(), TextStyle::Type::OutlineShadow) };
			Graphics2D::SetSDFParameters(TextStyle::OutlineShadow(0.2, ColorF{ 0.8, 0.4, 0.0 }, Vec2{ 2, 2 }, ColorF{ 0.0, 0.5 }));

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
}
