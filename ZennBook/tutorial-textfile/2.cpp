# include <Siv3D.hpp>

void Main()
{
	TextReader reader;

	// オープンに失敗
	if (not reader.open(U"example/txt/en.txt"))
	{
		throw Error{ U"Failed to open `en.txt`" };
	}

	// 行の内容を読み込む変数
	String line;

	// 行数の表示用のカウント
	size_t i = 0;

	// 1 行ずつ読み込む
	while (reader.readLine(line))
	{
		Print << U"{}: {}"_fmt(i++, line);
	}

	// ファイルを明示的にクローズ
	reader.close();

	while (System::Update())
	{

	}
}
