# include <Siv3D.hpp>

void Main()
{
	Texture texture;

	while (System::Update())
	{
		// テクスチャが空の状態で、左クリックされたら
		if ((not texture) && MouseL.down())
		{
			// テクスチャを作成して代入
			texture = Texture{ U"example/windmill.png" };
		}

		if (texture)
		{
			texture.draw();
		}
	}
}
