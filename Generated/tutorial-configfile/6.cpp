# include <Siv3D.hpp>

void Main()
{
	INI ini;

	// セクションを追加
	ini.addSection(U"Item");
	ini.addSection(U"Setting");

	ini.write(U"Item", U"Sword", 500);
	ini.write(U"Item", U"Arrow", 400);
	ini.write(U"Item", U"Shield", 300);
	ini.write(U"Item", U"Carrot Seed", 20);
	ini.write(U"Setting", U"pos", Point{ 20, 30 });
	ini.write(U"Setting", U"color", Palette::Red);

	// 保存
	ini.save(U"tutorial.ini");
	
	while (System::Update())
	{

	}
}
