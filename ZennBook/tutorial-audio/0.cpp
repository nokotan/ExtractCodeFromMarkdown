# include <Siv3D.hpp>

void Main()
{
	// 音声ファイルを読み込んで Audio を作成
	const Audio audio{ U"example/test.mp3" };

	// オーディオを再生
	audio.play();

	while (System::Update())
	{

	}
}
