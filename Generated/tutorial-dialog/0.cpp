# include <Siv3D.hpp>

void Main()
{
	// ファイルダイアログを使ってテクスチャをオープン
	Texture texture = Dialog::OpenTexture();

	while (System::Update())
	{
		if (texture)
		{
			// シーンのサイズにフィットさせて中心に描く
			texture.fitted(Scene::Size()).drawAt(Scene::Center());
		}

		if (SimpleGUI::Button(U"Open", Vec2{ 20,20 }))
		{
			// TextureDesc を指定することもできる
			texture = Dialog::OpenTexture(TextureDesc::Mipped);
		}
	}
}
