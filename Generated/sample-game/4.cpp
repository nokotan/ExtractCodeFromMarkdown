# include <Siv3D.hpp>

bool Swappable(int32 a, int32 b)
{
	return (a / 4 == b / 4 && Abs(a - b) == 1) || (a % 4 == b % 4 && Abs(a - b) == 4);
}

void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });
	constexpr int32 cellSize = 100;
	constexpr Point offset{ 60, 40 };

	// ダイアログから画像を選択
	const Image image = Dialog::OpenImage();

	// 正方形に切り抜く
	const Texture texture{ image.squareClipped(), TextureDesc::Mipped };

	Optional<int32> grabbed;

	// ランダムな操作でパズルをシャッフル
	Array<int32> pieces = Range(0, 15);
	{
		int32 pos15 = 15;

		for (int32 i = 0; i < 1000; ++i)
		{
			const int32 to = pos15 + Sample({ -4, -1, 1, 4 });

			if (InRange(to, 0, 15) && Swappable(pos15, to))
			{
				std::swap(pieces[pos15], pieces[to]);
				pos15 = to;
			}
		}
	}

	while (System::Update())
	{
		Rect{ offset, (4 * cellSize) }
			.drawShadow(Vec2{ 0, 2 }, 12, 8)
			.draw(ColorF{ 0.25 })
			.drawFrame(0, 8, ColorF{ 0.3, 0.5, 0.7 });

		if (not MouseL.pressed())
		{
			grabbed = none;
		}

		for (auto i : step(16))
		{
			const int32 pieceID = pieces[i];
			const Rect rect = Rect{ (i % 4 * cellSize), (i / 4 * cellSize), cellSize }.movedBy(offset);

			if (pieceID == 15)
			{
				if (grabbed && rect.mouseOver() && Swappable(i, grabbed.value()))
				{
					std::swap(pieces[i], pieces[grabbed.value()]);
					grabbed = i;
				}

				continue;
			}

			if (rect.leftClicked())
			{
				grabbed = i;
			}

			rect(texture.uv((pieceID % 4 * 0.25), (pieceID / 4 * 0.25), 0.25, 0.25))
				.draw()
				.drawFrame(1, 0, ColorF{ 1.0, 0.75 });

			if (grabbed == i)
			{
				rect.draw(ColorF{ 1.0, 0.5, 0.0, 0.3 });
			}

			if (rect.mouseOver())
			{
				Cursor::RequestStyle(CursorStyle::Hand);
			}
		}

		texture.resized(180)
			.draw((offset.x + cellSize * 4 + 40), offset.y)
			.drawFrame(0, 4, ColorF{ 0.3, 0.5, 0.7 });
	}
}
