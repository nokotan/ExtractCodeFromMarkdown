# include <Siv3D.hpp>

void Main()
{
	// ピアノの C4 (ド) の音
	const Audio pianoC{ GMInstrument::Piano1, PianoKey::C4, 0.5s };

	// ピアノの D4 (レ) の音
	const Audio pianoD{ GMInstrument::Piano1, PianoKey::D4, 0.5s };

	// ピアノの E4 (ミ) の音
	const Audio pianoE{ GMInstrument::Piano1, PianoKey::E4, 0.5s };

	double globalVolume = 1.0, mixBus0Volume = 1.0, mixBus1Volume = 1.0;

	while (System::Update())
	{
		if (SimpleGUI::Slider(U"Global Vol", globalVolume, Vec2{ 20, 20 }, 120, 200))
		{
			// グローバルオーディオの音量を変更
			GlobalAudio::SetVolume(globalVolume);
		}

		if (SimpleGUI::Slider(U"Bus0 Vol", mixBus0Volume, Vec2{ 20, 60 }, 120, 120))
		{
			// MixBus0 の音量を変更
			GlobalAudio::BusSetVolume(MixBus0, mixBus0Volume);
		}

		if (SimpleGUI::Slider(U"Bus1 Vol", mixBus1Volume, Vec2{ 300, 60 }, 120, 120))
		{
			// MixBus1 の音量を変更
			GlobalAudio::BusSetVolume(MixBus1, mixBus1Volume);
		}

		if (SimpleGUI::Button(U"C Bus0", Vec2{ 20, 100 }))
		{
			pianoC.playOneShot(MixBus0, 0.5);
		}

		if (SimpleGUI::Button(U"D Bus0", Vec2{ 20, 140 }))
		{
			pianoD.playOneShot(MixBus0, 0.5);
		}

		if (SimpleGUI::Button(U"E Bus0", Vec2{ 20, 180 }))
		{
			pianoE.playOneShot(MixBus0, 0.5);
		}

		if (SimpleGUI::Button(U"C Bus1", Vec2{ 300, 100 }))
		{
			pianoC.playOneShot(MixBus1, 0.5);
		}

		if (SimpleGUI::Button(U"D Bus1", Vec2{ 300, 140 }))
		{
			pianoD.playOneShot(MixBus1, 0.5);
		}

		if (SimpleGUI::Button(U"E Bus1", Vec2{ 300, 180 }))
		{
			pianoE.playOneShot(MixBus1, 0.5);
		}
	}
}
