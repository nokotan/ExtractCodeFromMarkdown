# include <Siv3D.hpp>

void Main()
{
	const Image image{ U"example/windmill.png" };

	// ガウスぼかしした画像からテクスチャを作成
	const Texture texture{ image.grayscaled() };

	while (System::Update())
	{
		texture.draw();
	}
}
