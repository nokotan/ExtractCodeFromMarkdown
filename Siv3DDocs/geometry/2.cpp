# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(Palette::White);

	const Circle circle{ Scene::Center(), 100 };

	int32 count = 0;

	while (System::Update())
	{
		ClearPrint();

		Print << count;

		// 円が左クリックされたら
		if (circle.leftClicked())
		{
			++count;
		}

		circle.draw(Palette::Gray);
	}
}
