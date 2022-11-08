# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		// "Licenses" ボタンが押されたら
		if (SimpleGUI::Button(U"Licenses", Vec2{ 20, 20 }))
		{
			// ライセンス情報を表示
			LicenseManager::ShowInBrowser();
		}
	}
}
