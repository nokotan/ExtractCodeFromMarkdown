# include <Siv3D.hpp>

void Main()
{
	// ファイルをオープンする
	TextReader reader{ U"example/txt/en.txt" };

	// オープンに失敗
	if (not reader)
	{
		// 例外を投げて終了
		throw Error{ U"Failed to open `en.txt`" };
	}

	// 行の内容を読み込む変数
	String line;

	// 行数の表示用のカウント
	size_t i = 0;

	// 終端に達するまで 1 行ずつ読み込む
	while (reader.readLine(line))
	{
		Print << i << U": " << line;
	}

	while (System::Update())
	{

	}

	// reader のデストラクタで自動的にファイルがクローズされる
}
