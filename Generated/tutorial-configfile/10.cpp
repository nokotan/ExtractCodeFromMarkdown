# include <Siv3D.hpp>

void Main()
{
	JSON json = JSON::Load(U"example/json/config.json");

	if (not json)
	{
		throw Error{ U"Failed to load `config.json`" };
	}

	// データを書き換える
	json[U"Window"][U"width"] = 1280;
	json[U"Window"][U"height"] = 720;

	// データを追加する
	json[U"Siv3D"][U"message"] = U"Hello!";

	// データを削除する
	json[U"Items"].erase(2);
	json.erase(U"Array");

	json.save(U"tutorial.json");

	while (System::Update())
	{

	}
}
