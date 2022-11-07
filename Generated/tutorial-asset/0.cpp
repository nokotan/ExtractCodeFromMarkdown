# include <Siv3D.hpp>

void Draw()
{
	// アセットの使用
	TextureAsset(U"Windmill").draw();
	TextureAsset(U"Siv3D-kun").scaled(0.8).drawAt(200, 200);
}

void Main()
{
	// アセットの登録
	TextureAsset::Register(U"Windmill", U"example/windmill.png");
	TextureAsset::Register(U"Siv3D-kun", U"example/siv3d-kun.png", TextureDesc::Mipped);

	while (System::Update())
	{
		Draw();
	}
}
