# include <Siv3D.hpp>

void Main()
{
	// 追加モードでテキストファイルをオープン
	TextWriter writer{ U"tutorial.txt", OpenMode::Append };

	// オープンに失敗
	if (not writer)
	{
		throw Error{ U"Failed to open `tutorial.txt`" };
	}

	// 文章を追加する
	writer.write(U"\n------");

	while (System::Update())
	{

	}
}
