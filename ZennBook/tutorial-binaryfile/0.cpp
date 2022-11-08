# include <Siv3D.hpp>

// ゲームのスコアを記録する構造体
struct GameScore
{
	int32 a, b, c, d;
};

void Main()
{
	// 書き込み用のバイナリファイルをオープン
	BinaryWriter writer{ U"tutorial1.bin" };

	if (not writer) // もしオープンに失敗したら
	{
		throw Error{ U"Failed to open `tutorial1.bin`" };
	}

	// int32 型の値 (4 バイト) を書き込む
	writer.write(777);

	// double 型の値 (8 バイト) を書き込む
	writer.write(3.1415);

	// Point 型の値 (8 バイト) を書き込む
	writer.write(Point{ 123, 456 });

	// GameScore 型の値 (16 バイト) を書き込む
	const GameScore s = { 10, 20, 30, 40 };
	writer.write(s);

	while (System::Update())
	{

	}

	// writer のデストラクタで自動的にファイルがクローズされる
}
