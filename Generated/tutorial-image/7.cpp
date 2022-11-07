# include <Siv3D.hpp>

Image MakeImage()
{
	Image image{ U"example/windmill.png" };

	for (auto& pixel : image)
	{
		// R 成分と B 成分を入れ替える
		std::swap(pixel.r, pixel.b);
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
