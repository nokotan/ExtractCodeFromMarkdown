# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		if (SimpleGUI::Button(U"Red", Vec2{ 100, 100 }))
		{
			Scene::SetBackground(ColorF{ 0.8, 0.2, 0.2 });
		}

		if (SimpleGUI::Button(U"Green", Vec2{ 100, 150 }))
		{
			Scene::SetBackground(ColorF{ 0.2, 0.8, 0.2 });
		}

		if (SimpleGUI::Button(U"Blue", Vec2{ 100, 200 }))
		{
			Scene::SetBackground(ColorF{ 0.2, 0.2, 0.8 });
		}

		// ボタンの幅を 200px に指定
		if (SimpleGUI::Button(U"White", Vec2{ 100, 250 }, 200))
		{
			Scene::SetBackground(ColorF{ 0.9 });
		}

		if (SimpleGUI::Button(U"Black", Vec2{ 100, 300 }, 200))
		{
			Scene::SetBackground(ColorF{ 0.1 });
		}

		// ボタンを無効化
		if (SimpleGUI::Button(U"Gray", Vec2{ 100, 350 }, 200, false))
		{
			Scene::SetBackground(ColorF{ 0.5 });
		}

		// ボタンを無効化、ボタンの幅はテキストに合わせる
		if (SimpleGUI::Button(U"Yellow", Vec2{ 100, 400 }, unspecified, false))
		{
			Scene::SetBackground(ColorF{ 0.8, 0.8, 0.1 });
		}
	}
}
