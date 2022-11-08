# include <Siv3D.hpp>

void Main()
{
	const Audio audio{ Audio::Stream, U"example/test.mp3" };

	while (System::Update())
	{
		ClearPrint();

		// 再生されているか
		Print << U"isPlaying: " << audio.isPlaying();

		// 一時停止中であるか
		Print << U"isPaused: " << audio.isPaused();

		if (SimpleGUI::Button(U"Play", Vec2{ 200, 20 }))
		{
			// 再生・再開
			audio.play();
		}

		if (SimpleGUI::Button(U"Pause", Vec2{ 200, 60 }))
		{
			// 一時停止
			audio.pause();
		}

		if (SimpleGUI::Button(U"Stop", Vec2{ 200, 100 }))
		{
			// 停止して再生位置を最初に戻す
			audio.stop();
		}
	}
}
