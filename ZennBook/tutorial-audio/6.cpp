# include <Siv3D.hpp>

void Main()
{
	const Audio audio{ Audio::Stream, U"example/test.mp3" };

	audio.play();

	while (System::Update())
	{
		ClearPrint();

		// 現在のスピード
		Print << audio.getSpeed();

		if (SimpleGUI::Button(U"1.2", Vec2{ 200, 20 }))
		{
			// 2 秒かけてスピードを 1.2 に
			audio.fadeSpeed(1.2, 2s);
		}

		if (SimpleGUI::Button(U"1.0", Vec2{ 200, 60 }))
		{
			// 1 秒かけてスピードを 1.0 に
			audio.fadeSpeed(1.0, 1s);
		}

		if (SimpleGUI::Button(U"0.8", Vec2{ 200, 100 }))
		{
			// 1.5 秒かけてスピードを 0.8 に
			audio.fadeSpeed(0.8, 1.5s);
		}
	}
}
