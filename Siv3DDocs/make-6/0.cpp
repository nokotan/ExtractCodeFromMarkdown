# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.9, 0.85, 0.8 });

	const Texture computerTexture{ U"🖥️"_emoji };
	const Texture boxTexture{ U"🗃️"_emoji };
	const Texture doorTexture{ U"🚪"_emoji };

	const Vec2 computerPos{ 200, 300 };
	const Vec2 boxPos{ 400, 300 };
	const Vec2 doorPos{ 600, 300 };

	while (System::Update())
	{
		computerTexture.drawAt(computerPos);
		boxTexture.drawAt(boxPos);
		doorTexture.drawAt(doorPos);

		if (const Circle circle{ computerPos, 80 };
			circle.mouseOver())
		{
			circle.draw(ColorF{ 1.0, 0.2 });
			Cursor::RequestStyle(CursorStyle::Hand);

			if (circle.leftClicked())
			{
				Print << U"パソコンだ。電源は入らない。";
			}
		}

		if (const Circle circle{ boxPos, 80 };
			circle.mouseOver())
		{
			circle.draw(ColorF{ 1.0, 0.2 });
			Cursor::RequestStyle(CursorStyle::Hand);

			if (circle.leftClicked())
			{
				Print << U"箱の中に何か入っている。部屋の鍵を見つけた！";
			}
		}

		if (const Circle circle{ doorPos, 80 };
			circle.mouseOver())
		{
			circle.draw(ColorF{ 1.0, 0.2 });
			Cursor::RequestStyle(CursorStyle::Hand);

			if (circle.leftClicked())
			{
				Print << U"ドアには鍵がかかっている。出られない。";
			}
		}
	}
}
