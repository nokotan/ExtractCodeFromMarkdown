# include <Siv3D.hpp>

void Main()
{
	const Audio audio{ Audio::Stream, U"example/test.mp3" };

	audio.play();

	double volume = 1.0;

	while (System::Update())
	{
		ClearPrint();

		// 現在の音量を取得
		Print << audio.getVolume();

		if (SimpleGUI::Slider(U"volume: {:.2f}"_fmt(volume), volume, Vec2{ 200, 20 }, 160, 140))
		{
			// 音量を設定
			audio.setVolume(volume);
		}
	}
}
