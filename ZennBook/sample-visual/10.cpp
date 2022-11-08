# include <Siv3D.hpp>

void Main()
{
	const Font font{ 75, Typeface::Light };
	const Array<char32> chars = Range(U'A', U'Z').asArray().append(Range(U'a', U'z'));
	const String targetText = U"C++/OpenSiv3D";

	Array<int32> delays = targetText.map([](auto) { return Random(20, 60); });
	String randomText = targetText;

	constexpr double displayTime = 0.05;
	double accumulator = 0.0;

	while (System::Update())
	{
		accumulator += Scene::DeltaTime();

		if (MouseL.down())
		{
			delays = targetText.map([](auto) { return Random(20, 60); });
		}

		if (displayTime <= accumulator)
		{
			accumulator -= displayTime;

			for (auto i : step(targetText.size()))
			{
				if (delays[i])
				{
					randomText[i] = chars.choice();
					--delays[i];
				}
				else
				{
					randomText[i] = targetText[i];
				}
			}
		}

		Vec2 penPos{ 50, 240 };

		for (auto [i, glyph] : Indexed(font.getGlyphs(targetText)))
		{
			const auto glyph2 = font.getGlyph(randomText[i]);

			glyph2.texture.draw(penPos + glyph2.getOffset());

			penPos.x += (glyph.xAdvance * 1.2);
		}
	}
}
