# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		if (SimpleGUI::Button(U"Center", Vec2{ 20, 20 }))
		{
			// ウィンドウを中心に移動
			Window::Centering();
		}
	}
}
