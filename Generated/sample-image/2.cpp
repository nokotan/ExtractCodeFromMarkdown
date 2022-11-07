# include <Siv3D.hpp>

void Main()
{
	Image image{ U"example/windmill.png" };
	DynamicTexture texture{ image };

	while (System::Update())
	{
		if (MouseL.down())
		{
			// Image 内の指定領域をガウスぼかし
			image(Cursor::Pos().movedBy(-30, -30), 60, 60)
				.gaussianBlur(25);

			texture.fill(image);
		}

		texture.draw();
	}
}
