# include <Siv3D.hpp>

void Main()
{
	Image image{ 600, 600, Palette::White };
	const Image emoji{ U"😃"_emoji };

	DynamicTexture dtexture{ image };

	while (System::Update())
	{
		if (MouseL.down())
		{
			emoji.paintAt(image, Cursor::Pos());

			// DynamicTexture の中身を Image で更新
			dtexture.fill(image);
		}

		dtexture.draw();
	}
}
