# include <Siv3D.hpp>

struct Building
{
	Texture icon;
	String name, desc;
};

void Main()
{
	Scene::SetBackground(ColorF{ 0.3, 0.6, 0.4 });
	const Font font1{ 30, Typeface::Heavy }, font2{ 15, Typeface::Medium };
	const Array<Texture> emojis = {
		Texture{ U"⚙️"_emoji }, Texture{ U"⚡"_emoji }, Texture{ U"♥"_emoji } };
	const Array<Building> buildings =
	{
		{ Texture{ U"🏭"_emoji }, U"工場", U"毎ターン 6$0 を生産する\n電力 3$1 が必要" },
		{ Texture{ U"🏟"_emoji }, U"スタジアム", U"毎ターン 4$2 を供給する\n電力 2$1 が必要" },
		{ Texture{ U"🏖"_emoji }, U"ビーチ", U"毎ターン 2$2 を供給する\n砂浜にしか建設できない" }
	};

	const RoundRect r0{ 0, 0, 360, 100, 6 };
	const RoundRect r1{ 5, 5, 90, 90, 5 };

	while (System::Update())
	{
		for (auto [i, building] : Indexed(buildings))
		{
			const Transformer2D t{ Mat3x2::Translate(40, (40 + i * 110)) };

			r0.drawShadow(Vec2{ 4, 4 }, 8, 1)
				.draw(ColorF{ 0.2, 0.25, 0.3 })
				.drawFrame(1, 1, ColorF{ 0.4, 0.5, 0.6 });
			r1.draw(ColorF{ 0.85, 0.9, 0.95 });
			building.icon.resized(80).drawAt(r1.center());
			font1(building.name).draw(r1.rect.pos.movedBy(100, 0));

			const Vec2 penPos0 = r1.rect.pos.movedBy(100, 42);
			Vec2 penPos = penPos0;
			bool onTag = false;

			for (const auto& glyph : font2.getGlyphs(building.desc))
			{
				if (onTag)
				{
					emojis[(glyph.codePoint - U'0')].resized(25).draw(penPos);
					penPos.x += 25;
					onTag = false;
					continue;
				}

				if (glyph.codePoint == U'$')
				{
					onTag = true;
					continue;
				}

				onTag = false;

				if (glyph.codePoint == U'\n')
				{
					penPos.x = penPos0.x;
					penPos.y += font2.height();
				}
				else
				{
					glyph.texture.draw(penPos + glyph.getOffset());
					penPos.x += glyph.xAdvance;
				}
			}
		}
	}
}
