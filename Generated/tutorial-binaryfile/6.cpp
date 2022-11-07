# include <Siv3D.hpp>

void Main()
{
	// バイナリファイルをオープン
	Deserializer<BinaryReader> reader{ U"tutorial3.bin" };

	if (not reader) // もしオープンに失敗したら
	{
		throw Error{ U"Failed to open `tutorial3.bin`" };
	}

	// 読み込み先のテキスト
	String text;

	// 読み込み先の変数
	int32 a, b;

	// バイナリファイルからシリアライズ対応型のデータを読み込む
	// （文字列や Array は自動でリサイズが行われる）
	reader(text);
	reader(a, b);

	Print << text.length();

	Print << text;

	Print << a << U", " << b;

	while (System::Update())
	{

	}

	// reader のデストラクタで自動的にファイルがクローズされる
}
