# include <Siv3D.hpp>

void Main()
{
	JSON json;

	json[U"Item"][U"Sword"][U"price"] = 500;
	json[U"Item"][U"Arrow"][U"price"] = 400;
	json[U"Item"][U"Shield"][U"price"] = 300;
	json[U"Item"][U"Carrot Seed"][U"price"] = 20;

	json[U"Setting"][U"pos"] = Point{ 20, 30 };
	json[U"Setting"][U"color"] = Palette::Red;

	json.save(U"tutorial.json");
	
	while (System::Update())
	{

	}
}
