# include <Siv3D.hpp>

void Main()
{
	Image image{ 600, 600, Palette::White };

	const Font font{ 60, Typeface::Bold };
	{
		const String text = U"Hello, Siv3D!\nこんにちは。";
		constexpr Vec2 basePos{ 20, 20 };
		Vec2 penPos{ basePos };

		for (const auto& ch : text)
		{
			// 改行文字なら
			if (ch == U'\n')
			{
				// ペンの X 座標をリセット
				penPos.x = basePos.x;

				// ペンの Y 座標をフォントの高さ分進める
				penPos.y += font.height();

				continue;
			}

			const BitmapGlyph bitmapGlyph = font.renderBitmap(ch);

			// 文字のテクスチャをペンの位置に文字ごとのオフセットを加算して描画
			// .asPoint() は Vec2 を Point に変換する関数
			bitmapGlyph.image.paint(image, (penPos + bitmapGlyph.getOffset()).asPoint(), Palette::Seagreen);

			// ペンの X 座標を文字の幅の分進める
			penPos.x += bitmapGlyph.xAdvance;
		}
	}

	const Texture texture{ image };

	while (System::Update())
	{
		texture.draw();
	}
}
