# include <Siv3D.hpp>

void Main()
{
	Scene::SetResizeMode(ResizeMode::Keep);
	Scene::Resize(200, 150);

	// 拡大縮小時に最近傍法で補間
	Scene::SetTextureFilter(TextureFilter::Nearest);

	const Texture texture{ U"🐈"_emoji };

	while (System::Update())
	{
		Circle{ 120, 75, 50 }.draw();

		texture.draw();
	}
}
