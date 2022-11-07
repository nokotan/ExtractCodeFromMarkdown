# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);
	Scene::SetBackground(Palette::Darkgreen);

	const PlayingCard::Pack pack{ 75, Palette::Red };
	Array<PlayingCard::Card> cards = PlayingCard::CreateDeck(2);

	while (System::Update())
	{
		for (auto i : step(13 * 4 + 2))
		{
			const Vec2 center{ 100 + i % 13 * 90, 100 + (i / 13) * 130 };

			if (pack.regionAt(center).mouseOver())
			{
				Cursor::RequestStyle(CursorStyle::Hand);

				if (MouseL.down())
				{
					cards[i].flip();
				}
			}

			pack(cards[i]).drawAt(center);
		}
	}
}
