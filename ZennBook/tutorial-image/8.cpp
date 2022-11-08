# include <Siv3D.hpp>

void Main()
{
	Image image{ U"example/windmill.png" };

	for (auto& pixel : image)
	{
		std::swap(pixel.r, pixel.b);
	}

	// 画像を保存
	image.save(U"tutorial1.png");

	while (System::Update())
	{

	}
}
