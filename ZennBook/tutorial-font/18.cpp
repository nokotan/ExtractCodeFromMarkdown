# include <Siv3D.hpp>

void Main()
{
	const Font font{ 50, Typeface::Bold };
	const String text = U"The quick brown fox\njumps over the lazy dog.";

	while (System::Update())
	{
		constexpr Vec2 basePos{ 20, 20 };
		Vec2 penPos{ basePos };

		// 文字単位で描画を制御するためのループ
		for (const auto& glyph : font.getGlyphs(text))
		{
			// 改行文字なら
			if (glyph.codePoint == U'\n')
			{
				// ペンの X 座標をリセット
				penPos.x = basePos.x;

				// ペンの Y 座標をフォントの高さ分進める
				penPos.y += font.height();

				continue;
			}

			// 位置に応じて色を変える
			const ColorF color = HSV{ penPos.x };

			// 文字のテクスチャをペンの位置に文字ごとのオフセットを加算して描画
			// FontMethod がビットマップ方式の場合に限り、Math::Round() で整数座標にすると品質が向上
			glyph.texture.draw(Math::Round(penPos + glyph.getOffset()), color);

			// ペンの X 座標を文字の幅の分進める
			penPos.x += glyph.xAdvance;
		}
	}
}
