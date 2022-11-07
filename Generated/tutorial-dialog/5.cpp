# include <Siv3D.hpp>

void Main()
{
	Optional<FilePath> path;

	while (System::Update())
	{
		ClearPrint();

		if (path)
		{
			Print << *path;
		}

		if (SimpleGUI::Button(U"Save PNG file", Vec2{ 20,100 }))
		{
			// ファイルセーブダイアログを使ってファイル名を選択
			// PNG ファイル
			path = Dialog::SaveFile({ FileFilter::PNG() });
		}

		if (SimpleGUI::Button(U"Save text file", Vec2{ 20,140 }))
		{
			// .txt
			path = Dialog::SaveFile({ FileFilter::Text() });
		}

		if (SimpleGUI::Button(U"Open .bin file", Vec2{ 20,180 }))
		{
			// 独自の拡張子
			path = Dialog::SaveFile({ { U"Binary file",{ U"bin" } } });
		}
	}
}
