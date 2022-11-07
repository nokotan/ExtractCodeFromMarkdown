# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.92 });

	// 歯車 (f013) のアイコン
	const Texture icon0{ 0xf013_icon, 40 };

	// 南京錠 (f023) のアイコン
	const Texture icon1{ 0xf023_icon, 80 };

	// 拡大鏡 (f00e) のアイコン
	const Texture icon2{ 0xf00e_icon, 120 };

	while (System::Update())
	{
		icon0.drawAt(200, 300, ColorF{ 0.25 });

		icon1.drawAt(400, 300, ColorF{ 0.25 });

		icon2.drawAt(600, 300, ColorF{ 0.25 });
	}
}
