# include <Siv3D.hpp>

Image MakeImage()
{
	return Image{ 400, 300, Color{ 63, 127, 255 } };
}

void Main()
{
	const Texture texture{ MakeImage() };

	while (System::Update())
	{
		texture.draw();
	}
}
