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

	const String text = reader.readAll();

	Print << text;

	while (System::Update())
	{

	}

	// reader のデストラクタで自動的にファイルがクローズされる
}
