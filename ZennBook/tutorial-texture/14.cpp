# include <Siv3D.hpp>

void Main()
{
	// 初期データを与えないと、空のテクスチャになる
	Texture textureA;

	if (not textureA)
	{
		Print << U"textureA is empty";
	}

	// 画像ファイルの読み込みに失敗すると、空のテクスチャになる
	Texture textureB{ U"aaa/bbb.png" };

	if (not textureB)
	{
		Print << U"textureB is empty";
	}

	while (System::Update())
	{
		textureA.draw(0, 0);

		textureB.draw(400, 0);
	}
}
