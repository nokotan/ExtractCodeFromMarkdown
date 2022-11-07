# include <Siv3D.hpp>

void Main()
{
	const Audio audio{ Audio::Stream, U"example/test.mp3" };

	audio.play();

	while (System::Update())
	{
		ClearPrint();

		// 現在のパン
		Print << audio.getPan();

		if (SimpleGUI::Button(U"0.9", Vec2{ 200, 20 }))
		{
			// 2 秒かけてパンを 0.9 に
			audio.fadePan(0.9, 2s);
		}

		if (SimpleGUI::Button(U"0.0", Vec2{ 200, 60 }))
		{
			// 1 秒かけてパンを 0.0 に
			audio.fadePan(0.0, 1s);
		}

		if (SimpleGUI::Button(U"-0.9", Vec2{ 200, 100 }))
		{
			// 1.5 秒かけてパンを -0.9 に
			audio.fadePan(-0.9, 1.5s);
		}
	}
}
