# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		ClearPrint();
		Print << Cursor::Pos();

		if (SimpleGUI::Button(U"center", Vec2{ 100, 20 }))
		{
			// マウスカーソルをシーンの中心に移動
			Cursor::SetPos(Scene::Center());
		}
	}
}
