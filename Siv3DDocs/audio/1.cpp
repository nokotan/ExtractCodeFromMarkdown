# include <Siv3D.hpp>

void Main()
{
	// 音声ファイルを読み込んで Audio を作成（ストリーミング再生をリクエスト）
	const Audio audio{ Audio::Stream, U"example/test.mp3" };

	// ストリーミング再生になるかを取得
	Print << audio.isStreaming();

	// オーディオを再生
	audio.play();

	while (System::Update())
	{

	}
}
