# include <Siv3D.hpp>

void Main()
{
	// フォルダ選択ダイアログを使ってフォルダを選択
	Optional<FilePath> path = Dialog::SelectFolder();

	while (System::Update())
	{
		ClearPrint();

		if (path)
		{
			Print << *path;
		}

		if (SimpleGUI::Button(U"Open", Vec2{ 20,100 }))
		{
			path = Dialog::SelectFolder();
		}
	}
}
