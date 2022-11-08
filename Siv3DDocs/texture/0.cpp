# include <Siv3D.hpp>

void Main()
{
	// 🐈 の絵文字からテクスチャを作成
	const Texture texture{ U"🐈"_emoji };

	while (System::Update())
	{
		// テクスチャを座標 (0, 0) を中心に描画
		texture.drawAt(0, 0);

		// テクスチャを座標 (200, 200) を中心に描画
		texture.drawAt(200, 200);

		// テクスチャを、シーン中央を中心にして描画
		texture.drawAt(Scene::Center());
	}
}
