# include <Siv3D.hpp>

void Main()
{
	// ハッシュテーブルの構築
	HashSet<String> table =
	{
		U"Red", U"Green", U"Black", U"White"
	};

	// エントリの追加
	table.emplace(U"Yellow");

	// エントリが存在するかを取得
	Print << table.contains(U"Green");
	Print << table.contains(U"Pink");

	// エントリを削除
	table.erase(U"Red");

	Print << U"---";

	for (const auto& key : table)
	{
		Print << key;
	}

	while (System::Update())
	{

	}
}
