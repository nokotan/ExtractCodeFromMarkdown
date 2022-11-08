# include <Siv3D.hpp>

void Main()
{
	// 円をつかんでいるか
	bool grab = false;

	Circle circle{ Scene::Center(), 50 };

	while (System::Update())
	{
		if (grab)
		{
			// 移動量分だけ円を移動
			circle.moveBy(Cursor::Delta());
		}

		if (circle.leftClicked()) // 円を左クリックしたら
		{
			grab = true;
		}
		else if (MouseL.up()) // マウスの左ボタンが離されたら
		{
			grab = false;
		}

		if (grab || circle.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}

		circle.draw(Palette::Skyblue);
	}
}
