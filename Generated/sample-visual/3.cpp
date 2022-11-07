# include <Siv3D.hpp>

void Main()
{
	const Array<Texture> textures =
	{
		Texture{ U"💹"_emoji },
		Texture{ U"📅"_emoji },
		Texture{ U"🏡"_emoji },
	};

	constexpr Size imageSize = Emoji::ImageSize;

	while (System::Update())
	{
		Rect{ 0, 300, 800, 300 }.draw(ColorF{ 0.2, 0.3, 0.4 });

		for (auto [i, texture] : Indexed(textures))
		{
			const Vec2 pos{ (140 + i * 200), 220 };

			texture.draw(pos);

			// 反射するテクスチャ
			texture(0, (imageSize.y / 2), imageSize.x, (imageSize.y / 2))
				.flipped()
				.draw(pos.x, (pos.y + imageSize.y),
					Arg::top = AlphaF(0.8), Arg::bottom = AlphaF(0.0));
		}
	}
}
