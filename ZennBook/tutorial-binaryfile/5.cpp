# include <Siv3D.hpp>

void Main()
{
	// 書き込み用のバイナリファイルをオープン
	Serializer<BinaryWriter> writer{ U"tutorial3.bin" };

	if (not writer) // もしオープンに失敗したら
	{
		throw Error{ U"Failed to open `tutorial3.bin`" };
	}

	// 書き込みたいテキスト
	const String text = U"Hello, Siv3D";

	// 書き込みたいデータ
	int a = 123, b = 456;

	// バイナリファイルにシリアライズ対応型のデータを書き込む
	writer(text);

	// まとめて記述することもできる
	writer(a, b);

	while (System::Update())
	{

	}

	// writer のデストラクタで自動的にファイルがクローズされる
}
