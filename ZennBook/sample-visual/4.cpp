# include <Siv3D.hpp>

// Glyph とエフェクトの関数を組み合わせてテキストを描画
void DrawText(const Font& font, const String& text, const Vec2& pos, const ColorF& color, double t,
	void f(const Vec2&, const Glyph&, const ColorF&, double), double characterdPerSec)
{
	Vec2 penPos = pos;

	for (auto[i, glyph] : Indexed(font.getGlyphs(text)))
	{
		if (glyph.codePoint == U'\n')
		{
			penPos.x = pos.x;
			penPos.y += font.height();
			continue;
		}

		const double targetTime = (i * characterdPerSec);

		if (t < targetTime)
		{
			break;
		}

		f(penPos, glyph, color, (t - targetTime));

		penPos.x += glyph.xAdvance;
	}
}

// 文字が上からゆっくり降ってくる表現
void TextEffect1(const Vec2& penPos, const Glyph& glyph, const ColorF& color, double t)
{
	const double y = EaseInQuad(Saturate(1 - t / 0.3)) * -20.0;
	const double a = Min(t / 0.3, 1.0);
	glyph.texture.draw(penPos + glyph.getOffset() + Vec2{ 0, y }, ColorF{ color, a });
}

// 文字が勢いよく現れる表現
void TextEffect2(const Vec2& penPos, const Glyph& glyph, const ColorF& color, double t)
{
	const double s = Min(t / 0.1, 1.0);
	const double a = Min(t / 0.2, 1.0);
	glyph.texture.scaled(3.0 - s * 2).draw(penPos + glyph.getOffset(), ColorF{ color, a });
}

// 落ちてきた文字がしばらく揺れる表現
void TextEffect3(const Vec2& penPos, const Glyph& glyph, const ColorF& color, double t)
{
	const double angle = Sin(t * 1440_deg) * 25_deg * Saturate(1.0 - t / 0.6);
	const double y = Saturate(1 - t / 0.05) * -20.0;
	glyph.texture.rotated(angle).draw(penPos + glyph.getOffset() + Vec2{ 0, y }, color);
}

void Main()
{
	const Font font{ 32, Typeface::Bold };
	const String text = U"Lorem ipsum dolor sit amet, consectetur\n"
		U"adipiscing elit, sed do eiusmod tempor\n"
		U"incididunt ut labore et dolore magna aliqua.";

	Stopwatch stopwatch{ StartImmediately::Yes };

	while (System::Update())
	{
		if (SimpleGUI::Button(U"Reset", Vec2{ 620, 520 }))
		{
			stopwatch.restart();
		}

		const double t = stopwatch.sF();
		DrawText(font, text, Vec2{ 40, 40 }, Palette::Skyblue, t, TextEffect1, 0.1);
		DrawText(font, text, Vec2{ 40, 200 }, Palette::Orange, t, TextEffect2, 0.1);
		DrawText(font, text, Vec2{ 40, 360 }, Palette::Seagreen, t, TextEffect3, 0.1);
	}
}
