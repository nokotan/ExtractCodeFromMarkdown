# include <Siv3D.hpp>

void Main()
{
	// 1.5 秒～44.5 秒の区間をループ
	const Audio audio{ U"example/test.mp3", Arg::loopBegin = 1.5s, Arg::loopEnd = 44.5s };

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
