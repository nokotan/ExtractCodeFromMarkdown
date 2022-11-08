# include <Siv3D.hpp>

Image MakeImage()
{
	Image image{ 400, 300 };

	for (auto p : step(image.size()))
	{
		image[p] = ColorF{ (p.x / 399.0), (p.y / 299.0), 1.0 };
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
