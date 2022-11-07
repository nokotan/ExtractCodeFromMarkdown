# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		if (SimpleGUI::Button(U"How to play", Vec2{ 20, 20 }))
		{
			// Web ページをブラウザで開く
			System::LaunchBrowser(U"https://zenn.dev/reputeless/books/siv3d-documentation");
		}
	}
}
