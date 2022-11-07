# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);
	Scene::SetBackground(ColorF{ 0.99, 0.96, 0.93 });

	const Font font{ 130, U"example/font/RocknRoll/RocknRollOne-Regular.ttf" };
	const Array<OutlineGlyph> glyphs = font.renderOutlines(U"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890!?");

	while (System::Update())
	{
		const double t = Periodic::Sawtooth0_1(2.6s);
		const double len = Periodic::Sine0_1(16s) * 0.5;
		constexpr Vec2 basePos{ 70, 0 };
		Vec2 penPos{ basePos };

		for (const auto& glyph : glyphs)
		{
			const Transformer2D transform{ Mat3x2::Translate(penPos + glyph.getOffset()) };

			for (const auto& ring : glyph.rings)
			{
				const double length = ring.calculateLength(CloseRing::Yes);
				LineString z1 = ring.extractLineString(t * length, length * len, CloseRing::Yes);
				const LineString z2 = ring.extractLineString((t + 0.5) * length, length * len, CloseRing::Yes);
				z1.append(z2.reversed()).drawClosed(3, ColorF{ 0.25 });
			}

			if (penPos.x += glyph.xAdvance;
				1120 < penPos.x)
			{
				penPos.x = basePos.x;
				penPos.y += font.fontSize();
			}
		}
	}
}
