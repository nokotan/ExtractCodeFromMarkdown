# include <Siv3D.hpp>

Image MakeImage()
{
	Image image{ 400, 300 };

	for (int32 y = 0; y < image.height(); ++y)
	{
		for (int32 x = 0; x < image.width(); ++x)
		{
			image[y][x] = ColorF{ (x / 399.0), (y / 299.0), 1.0 };
		}
	}

	return image;
}

void Main()
{
	const Texture texture{ MakeImage() };

	while (System::Update())
	{
		texture.draw();
	}
}
