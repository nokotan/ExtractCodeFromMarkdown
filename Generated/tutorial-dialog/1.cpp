# include <Siv3D.hpp>

void Main()
{
	// ファイルダイアログを使ってオーディオをオープン
	Audio audio = Dialog::OpenAudio();

	while (System::Update())
	{
		if (audio && (not audio.isPlaying()))
		{
			audio.play();
		}

		if (SimpleGUI::Button(U"Open", Vec2{ 20,20 }))
		{
			// Audio::Stream を指定することもできる
			audio = Dialog::OpenAudio(Audio::Stream);
		}
	}
}
