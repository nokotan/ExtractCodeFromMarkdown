# include <Siv3D.hpp>

void Main()
{
	// ファイルオープンダイアログを使ってファイルを選択
	Optional<FilePath> path = Dialog::OpenFile({ FileFilter::AllFiles() });

	while (System::Update())
	{
		ClearPrint();

		if (path)
		{
			Print << *path;
		}

		if (SimpleGUI::Button(U"Open image file", Vec2{ 20,100 }))
		{
			// 画像ファイル
			path = Dialog::OpenFile({ FileFilter::AllImageFiles() });
		}

		if (SimpleGUI::Button(U"Open text file", Vec2{ 20,140 }))
		{
			// .txt
			path = Dialog::OpenFile({ FileFilter::Text() });
		}

		if (SimpleGUI::Button(U"Open .bin file", Vec2{ 20,180 }))
		{
			// 独自の拡張子
			path = Dialog::OpenFile({ { U"Binary file",{ U"bin" } } });
		}
	}
}
