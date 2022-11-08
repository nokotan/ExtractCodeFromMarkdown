# include <Siv3D.hpp>

void Main()
{
	// 初期データを与えないと、空のオーディオになる
	Audio audioA;

	if (not audioA)
	{
		Print << U"audioA is empty";
	}

	// 音声ファイルの読み込みに失敗すると、空のオーディオになる
	Audio audioB{ U"aaa/bbb.wav" };

	if (not audioB)
	{
		Print << U"audioB is empty";
	}

	while (System::Update())
	{
		if (SimpleGUI::Button(U"Play A", Vec2{ 200, 20 }))
		{
			audioA.playOneShot();
		}

		if (SimpleGUI::Button(U"Play B", Vec2{ 200, 60 }))
		{
			audioB.playOneShot();
		}
	}
}
