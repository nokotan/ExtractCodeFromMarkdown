# include <Siv3D.hpp>

void Main()
{
	INI ini{ U"example/ini/config.ini" };

	if (not ini)
	{
		throw Error{ U"Failed to load `config.ini`" };
	}

	// データを書き換える
	ini[U"Window.width"] = 1280;
	ini[U"Window.height"] = 720;

	// データを追加する
	ini.addSection(U"Siv3D");
	ini.write(U"Siv3D", U"message", U"Hello!");

	// データを削除する
	ini.removeSection(U"Item2");

	ini.save(U"tutorial.ini");

	while (System::Update())
	{

	}
}
