# include <Siv3D.hpp>

void Main()
{
	AudioAsset::Register({ U"BGM-0", { U"BGM" } }, Audio::Stream, U"example/test.mp3");
	AudioAsset::Register({ U"BGM-1", { U"BGM" } }, U"example/midi/test.mid");
	AudioAsset::Register({ U"PianoC", { U"SE", U"Piano" } }, GMInstrument::Piano1, PianoKey::C4, 0.5s);
	AudioAsset::Register({ U"PianoD", { U"SE", U"Piano" } }, GMInstrument::Piano1, PianoKey::D4, 0.5s);
	AudioAsset::Register({ U"PianoE", { U"SE", U"Piano" } }, GMInstrument::Piano1, PianoKey::E4, 0.5s);
	AudioAsset::Register({ U"TrumpetC", { U"SE", U"Trumpet" } }, GMInstrument::Trumpet, PianoKey::C4, 0.5s);
	AudioAsset::Register({ U"TrumpetD", { U"SE", U"Trumpet" } }, GMInstrument::Trumpet, PianoKey::D4, 0.5s);
	AudioAsset::Register({ U"TrumpetE", { U"SE", U"Trumpet" } }, GMInstrument::Trumpet, PianoKey::E4, 0.5s);

	for (auto[name, info] : AudioAsset::Enumerate())
	{
		Print << name << U": " << info.tags;

		// U"SE" というタグを持つアセットだけロード
		if (info.tags.includes(U"SE"))
		{
			AudioAsset::Load(name);
		}
	}

	Print << U"---";
	Print << AudioAsset::IsReady(U"BGM-0");
	Print << AudioAsset::IsReady(U"BGM-1");
	Print << AudioAsset::IsReady(U"PianoC");
	Print << AudioAsset::IsReady(U"PianoD");
	Print << AudioAsset::IsReady(U"PianoE");
	Print << AudioAsset::IsReady(U"TrumpetC");
	Print << AudioAsset::IsReady(U"TrumpetD");
	Print << AudioAsset::IsReady(U"TrumpetE");

	while (System::Update())
	{

	}
}
