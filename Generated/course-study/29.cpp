# include <Siv3D.hpp>

void Main()
{
	const Texture cat{ U"🐈"_emoji };

	while (System::Update())
	{
		// 画像中の (40, 20) を軸に回転させて描画
		cat.rotatedAt(Vec2{ 40, 20 }, Scene::Time() * 90_deg).draw(Scene::Center());
	}
}
