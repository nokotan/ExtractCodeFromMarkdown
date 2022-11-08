# include <Siv3D.hpp>

void Main()
{
	const Audio audio{ Audio::Stream, U"example/test.mp3", Loop::Yes };

	audio.play();

	while (System::Update())
	{
		ClearPrint();

		// ループが設定されているか
		Print << audio.isLoop();

		// ループ回数
		Print << audio.loopCount();

		// 曲全体
		Print << U"all: {:.1f} sec ({} samples)"_fmt(audio.lengthSec(), audio.samples());

		// 再生位置
		Print << U"play: {:.1f} sec ({} samples)"_fmt(audio.posSec(), audio.posSample());
	}
}
