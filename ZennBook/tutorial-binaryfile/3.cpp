# include <Siv3D.hpp>

void Main()
{
	// 書き込み用のバイナリファイルをオープン
	BinaryWriter writer{ U"tutorial2.bin" };

	if (not writer) // もしオープンに失敗したら
	{
		throw Error{ U"Failed to open `tutorial2.bin`" };
	}

	// 書き込みたいテキスト
	const String text = U"Hello, Siv3D";

	// 書き込みたいテキストの長さ
	const uint64 length = text.length();

	// テキストの長さを書き込む (8 バイト)
	writer.write(length);

	// 格納されてるデータの先頭ポインタから
	// (4 バイト × 長さ）分のテキストデータを書き込む 
	writer.write(text.data(), (sizeof(char32) * length));

	while (System::Update())
	{

	}

	// writer のデストラクタで自動的にファイルがクローズされる
}
