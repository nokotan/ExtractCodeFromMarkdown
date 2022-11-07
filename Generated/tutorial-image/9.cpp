# include <Siv3D.hpp>

void Main()
{
	Image image{ U"example/windmill.png" };

	for (auto& pixel : image)
	{
		std::swap(pixel.r, pixel.b);
	}

	// ダイアログでファイル名を指定して画像を保存
	image.saveWithDialog();

	while (System::Update())
	{

	}
}
