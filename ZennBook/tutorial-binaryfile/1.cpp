# include <Siv3D.hpp>

// ゲームのスコアを記録する構造体
struct GameScore
{
	int32 a, b, c, d;
};

void Main()
{
	// 先ほどのサンプルで作ったバイナリファイルをオープン
	BinaryReader reader{ U"tutorial1.bin" };

	if (not reader) // もしオープンに失敗したら
	{
		throw Error{ U"Failed to open `tutorial1.bin`" };
	}

	// int32 型の値 (4 バイト) を読み込む
	int32 n;
	reader.read(n);
	Print << n;

	// double 型の値 (8 バイト) を読み込む
	double d;
	reader.read(d);
	Print << d;

	// Point 型の値 (8 バイト) を読み込む
	Point pos;
	reader.read(pos);
	Print << pos;

	// GameScore 型の値 (16 バイト) を読み込む
	GameScore s;
	reader.read(s);
	Print << U"{}, {}, {}, {}"_fmt(s.a, s.b, s.c, s.d);

	while (System::Update())
	{

	}

	// reader のデストラクタで自動的にファイルがクローズされる
}
