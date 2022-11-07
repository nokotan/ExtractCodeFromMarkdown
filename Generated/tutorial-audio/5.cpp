# include <Siv3D.hpp>

void Main()
{
	const Audio audio{ Audio::Stream, U"example/test.mp3" };

	audio.play();

	while (System::Update())
	{
		ClearPrint();

		// 現在の音量
		Print << audio.getVolume();

		if (SimpleGUI::Button(U"1.0", Vec2{ 200, 20 }))
		{
			// 2 秒かけて音量を 1.0 に
			audio.fadeVolume(1.0, 2s);
		}

		if (SimpleGUI::Button(U"0.5", Vec2{ 200, 60 }))
		{
			// 1 秒かけて音量を 0.5 に
			audio.fadeVolume(0.5, 1s);
		}

		if (SimpleGUI::Button(U"0.1", Vec2{ 200, 100 }))
		{
			// 1.5 秒かけて音量を 0.1 に
			audio.fadeVolume(0.1, 1.5s);
		}
	}
}
