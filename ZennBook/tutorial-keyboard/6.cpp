# include <Siv3D.hpp>

void Main()
{
	InputGroup inputLeft = KeyLeft;
	InputGroup inputRight = KeyRight;
	InputGroup inputJump = KeySpace;
	size_t index = 0;

	const Array<String> options
	{
		U"[←] [→] [Space]",
		U"[A] [D] [W]",
		U"[←]/[A] [→]/[D] [Space]/[W]"
	};

	const Texture texture{ U"🐥"_emoji };
	Vec2 pos{ 400, 450 };
	double jumpY = 0.0;

	while (System::Update())
	{
		// 🐥 の移動
		{
			const double deltaTime = Scene::DeltaTime();

			if (inputLeft.pressed())
			{
				pos.x -= (deltaTime * 200);
			}

			if (inputRight.pressed())
			{
				pos.x += (deltaTime * 200);
			}

			if (inputJump.down())
			{
				jumpY = 500.0;
			}

			pos.y = Min(pos.y - deltaTime * jumpY, 450.0);
			jumpY = Max(jumpY - deltaTime * 1000.0, -1000.0);
		}

		// 背景と 🐥 の描画
		{
			Rect{ 800, 500 }
			.draw(Arg::top = ColorF{ 0.1, 0.4, 0.8 }, Arg::bottom = ColorF{ 0.4, 0.7, 1.0 });
			Rect{ 0, 500, 800, 100 }
			.draw(ColorF{ 0.2, 0.5, 0.3 });

			texture.drawAt(pos);
		}

		// キーコンフィグ
		if (SimpleGUI::RadioButtons(index, options, Vec2{ 20, 20 }))
		{
			if (index == 0)
			{
				inputLeft = KeyLeft;
				inputRight = KeyRight;
				inputJump = KeySpace;
			}
			else if (index == 1)
			{
				inputLeft = KeyA;
				inputRight = KeyD;
				inputJump = KeyW;
			}
			else
			{
				inputLeft = (KeyLeft | KeyA);
				inputRight = (KeyRight | KeyD);
				inputJump = (KeySpace | KeyW);
			}
		}
	}
}
