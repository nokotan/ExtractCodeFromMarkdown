# include <Siv3D.hpp>

void Main()
{
	CSV csv;

	// 1 行書き込む場合
	csv.writeRow(U"item", U"price");
	csv.writeRow(U"Sword", 500);

	// 1 項目ずつ書き込む場合
	csv.write(U"Arrow");
	csv.write(400);
	csv.newLine();

	csv.writeRow(U"Shield", 300);
	csv.writeRow(U"Carrot Seed", 20);
	csv.writeRow(Point{ 20,30 }, Palette::Red);

	// 保存
	csv.save(U"tutorial.csv");
	
	while (System::Update())
	{

	}
}
