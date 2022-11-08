# include <Siv3D.hpp>

void Main()
{
	CSV csv{ U"example/csv/config.csv" };

	if (not csv)
	{
		throw Error{ U"Failed to load `config.csv`" };
	}

	// データを書き換える
	csv[2][1] = Format(1280);
	csv[3][1] = Format(720);

    // データを追加する
    csv.writeRow(U"Hello.Siv3D", 12345);

	csv.save(U"tutorial.csv");

	while (System::Update())
	{

	}
}
