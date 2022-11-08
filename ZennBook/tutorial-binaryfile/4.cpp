# include <Siv3D.hpp>

void Main()
{
	// バイナリファイルをオープン
	BinaryReader reader{ U"tutorial2.bin" };

	if (not reader) // もしオープンに失敗したら
	{
		throw Error{ U"Failed to open `tutorial2.bin`" };
	}

	// 書き込みたいテキストの長さ
	uint64 length = 0;

	// 書き込みたいテキスト
	String text;

	// テキストの長さを読み込む
	reader.read(length);

	if (0 < length)
	{
		// テキストデータの読み込みのためにリサイズ
		text.resize(length);

		// テキストのサイズ分だけデータを読み込む
		reader.read(text.data(), (sizeof(char32) * length));
	}

	Print << length;

	Print << text;

	while (System::Update())
	{

	}

	// reader のデストラクタで自動的にファイルがクローズされる
}
