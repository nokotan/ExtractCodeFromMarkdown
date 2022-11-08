# include <Siv3D.hpp>

void Main()
{
	// ピアノの C4 (ド) の音
	const Audio piano{ GMInstrument::Piano1, PianoKey::C4, 0.5s };

	// クラリネットの D4 (レ) の音
	const Audio clarinet{ GMInstrument::Clarinet, PianoKey::D4, 0.5s };

	// トランペットの E4 (ミ) の音。ノート・オン 2.0 秒、ノート・オフ 0.5 秒
	const Audio trumpet{ GMInstrument::Trumpet, PianoKey::E4, 2.0s, 0.5s };

	while (System::Update())
	{
		if (SimpleGUI::Button(U"Piano", Vec2{ 20, 20 }))
		{
			piano.play();
		}

		if (SimpleGUI::Button(U"Clarinet", Vec2{ 20, 60 }))
		{
			clarinet.play();
		}

		if (SimpleGUI::Button(U"Trumpet", Vec2{ 20, 100 }))
		{
			trumpet.play();
		}
	}
}
