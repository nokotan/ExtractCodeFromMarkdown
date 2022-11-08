# include <Siv3D.hpp>

void MakeSound()
{
	// アセットの使用
	AudioAsset(U"Sound").playOneShot();
}

void Main()
{
	// アセットの登録
	AudioAsset::Register(U"BGM", U"example/test.mp3");
	AudioAsset::Register(U"Sound", GMInstrument::Piano1, PianoKey::A4, 0.5s);

	// アセットの使用
	AudioAsset(U"BGM").setVolume(0.2);
	AudioAsset(U"BGM").play();

	while (System::Update())
	{
		if (MouseL.down())
		{
			MakeSound();
		}
	}
}
