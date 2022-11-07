# include <Siv3D.hpp>

void Main()
{
	Image image{ 600, 600, Palette::White };

	const Image windmillImage{ U"example/windmill.png" };
	const Image catImage{ U"🐈"_emoji };

	windmillImage.overwrite(image, 40, 40);

	// 透過ピクセルに対する paint / stamp / overwrite の違い
	Rect{ 100, 400, 400, 40 }.overwrite(image, Color{ 255, 0 });
	catImage.paintAt(image, 150, 400);
	catImage.stampAt(image, 300, 400);
	catImage.overwriteAt(image, 450, 400);

	const Texture texture{ image };

	while (System::Update())
	{
		texture.draw();
	}
}
