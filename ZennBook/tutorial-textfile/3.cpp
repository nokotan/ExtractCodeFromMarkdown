# include <Siv3D.hpp>

void Main()
{
	// 書き込み用のファイルをオープンする
	// （同名のファイルがすでに存在する場合はそれを破棄してからオープン）
	TextWriter writer(U"tutorial.txt");

	// オープンに失敗
	if (not writer)
	{
		throw Error{ U"Failed to open `tutorial.txt`" };
	}

	// 文章を 1 行書き込む
	writer << U"Hello, Siv3D!";

	// 値や文字を　1 行書き込む
	writer << 123 << U',' << 456 << Point{ 10, 20 };

	// 1 文字ずつ書き込む（改行無し）
	writer.write(U'A');
	writer.write(U'B');

	// 1 文字書き込んで改行も書き込む
	writer.writeln(U'C');

	// 値を書き込む（改行無し）
	writer.write(777);
	writer.write(U',');
	writer.write(888);

	while (System::Update())
	{

	}

	// writer のデストラクタで自動的にファイルがクローズされる
}
