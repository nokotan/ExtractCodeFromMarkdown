# include <Siv3D.hpp>

void Main()
{
	// ハッシュテーブルの構築
	HashTable<String, int32> table =
	{ 
		{ U"Red", 1 },
		{ U"Green", 2 },
		{ U"Black", 3 },
		{ U"White", 4 },
	};

	// エントリの追加
	table.emplace(U"Yellow", 5);

	// 値のルックアップ
	Print << table[U"Red"];
	Print << table[U"White"];

	// エントリが存在するかを取得
	Print << table.contains(U"Green");
	Print << table.contains(U"Pink");

	// エントリの削除
	table.erase(U"Red");

	// イテレータを使ったループと値の変更
	for (auto it = table.begin(); it != table.end(); ++it)
	{
		it->second += 100;
	}

	Print << U"---";

	// 値を変更しないループはこの書き方もできる
	for (auto [key, value] : table)
	{
		Print << key << U": " << value;
	}

	while (System::Update())
	{

	}
}
