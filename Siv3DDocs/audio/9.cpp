# include <Siv3D.hpp>

void Main()
{
	const Audio audio{ Audio::Stream, U"example/test.mp3" };

	audio.play();

	while (System::Update())
	{
		ClearPrint();

		// 曲全体
		Print << U"all: {:.1f} sec ({} samples)"_fmt(audio.lengthSec(), audio.samples());

		// 再生位置
		Print << U"play: {:.1f} sec ({} samples)"_fmt(audio.posSec(), audio.posSample());

		if (SimpleGUI::Button(U"0 samples", Vec2{ 300, 20 }))
		{
			// 0 サンプル目（曲の先頭）に移動
			audio.seekSamples(0);
		}

		if (SimpleGUI::Button(U"441,000 samples", Vec2{ 300, 60 }))
		{
			// 441,000 サンプル目に移動
			audio.seekSamples(441000);
		}

		if (SimpleGUI::Button(U"20.0 sec", Vec2{ 300, 100 }))
		{
			// 20 秒の位置に移動
			audio.seekTime(20.0);
		}
	}
}
