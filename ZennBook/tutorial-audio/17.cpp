# include <Siv3D.hpp>

void Main()
{
	Audio audio;

	while (System::Update())
	{
		ClearPrint();

		Print << audio.isEmpty();

		// オーディオが空の状態で、左クリックされたら
		if ((not audio) && MouseL.down())
		{
			// オーディオを作成して代入
			audio = Audio{ Audio::Stream, U"example/test.mp3" };

			audio.play();
		}
	}
}
