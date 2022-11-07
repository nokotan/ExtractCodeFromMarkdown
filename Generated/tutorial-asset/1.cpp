# include <Siv3D.hpp>

void Draw()
{
	// アセットの使用
	FontAsset(U"Title")(U"My Game").drawAt(400, 100);
	FontAsset(U"Menu")(U"Play").drawAt(400, 400);
	FontAsset(U"Menu")(U"Exit").drawAt(400, 500);
}

void Main()
{
	// アセットの登録
	FontAsset::Register(U"Title", 60, U"example/font/RocknRoll/RocknRollOne-Regular.ttf");
	FontAsset::Register(U"Menu", 40, Typeface::Medium);

	while (System::Update())
	{
		Draw();
	}
}
