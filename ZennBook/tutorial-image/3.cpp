# include <Siv3D.hpp>

void Main()
{
	const Image image{ 400, 300, Color{ 63, 127, 255 } };

	const Texture texture{ image };

	while (System::Update())
	{
		texture.draw();
	}
}
