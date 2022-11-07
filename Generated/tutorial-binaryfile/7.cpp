# include <Siv3D.hpp>

// ユーザデータとゲームのスコアを記録する構造体
struct GameScore
{
	String name;

	int32 id;

	int32 score;

	// シリアライズに対応させるためのメンバ関数を定義する
	template <class Archive>
	void SIV3D_SERIALIZE(Archive& archive)
	{
		archive(name, id, score);
	}
};

void Main()
{
	{
		// 記録したいデータ
		const Array<GameScore> scores =
		{
			{ U"Player1", 111, 1000 },
			{ U"Player2", 222, 2000 },
			{ U"Player3", 333, 3000 },
		};

		// バイナリファイルをオープン
		Serializer<BinaryWriter> writer{ U"tutorial4.bin" };

		if (not writer) // もしオープンに失敗したら
		{
			throw Error{ U"Failed to open `tutorial4.bin`" };
		}

		// シリアライズに対応したデータを記録
		writer(scores);

		// writer のデストラクタで自動的にファイルがクローズされる
	}

	// 読み込み先のデータ
	Array<GameScore> scores;
	{
		// バイナリファイルをオープン
		Deserializer<BinaryReader> reader{ U"tutorial4.bin" };

		if (not reader) // もしオープンに失敗したら
		{
			throw Error{ U"Failed to open `tutorial4.bin`" };
		}

		// バイナリファイルからシリアライズ対応型のデータを読み込む
		// （Array は自動でリサイズが行われる）
		reader(scores);

		// reader のデストラクタで自動的にファイルがクローズされる
	}

	// 読み込んだスコアを確認
	for (const auto& score : scores)
	{
		Print << U"{}(id: {}): {}"_fmt(score.name, score.id, score.score);
	}

	while (System::Update())
	{

	}
}
