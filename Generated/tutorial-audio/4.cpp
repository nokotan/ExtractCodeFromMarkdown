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

		// 現在の音量
		Print << audio.getVolume();

		if (SimpleGUI::Button(U"Play", Vec2{ 200, 20 }))
		{
			// 2 秒かけて再生・再開
			audio.play(2s);
		}

		if (SimpleGUI::Button(U"Pause", Vec2{ 200, 60 }))
		{
			// 2 秒かけて一時停止
			audio.pause(2s);
		}

		if (SimpleGUI::Button(U"Stop", Vec2{ 200, 100 }))
		{
			// 2 秒かけて停止して再生位置を最初に戻す
			audio.stop(2s);
		}
	}
}
