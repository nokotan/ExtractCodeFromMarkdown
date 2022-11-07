# include <Siv3D.hpp>

void Main()
{
	// 🐈 の絵文字からテクスチャを作成
	const Texture texture{ U"🐈"_emoji };

	while (System::Update())
	{
		// テクスチャを座標 (400, 0) から描画
		texture.draw(400, 0);

		// 座標を指定しない場合 (0, 0) から描画
		texture.draw();

		// テクスチャをシーン中心から描画
		texture.draw(Scene::Center());
	}
}
