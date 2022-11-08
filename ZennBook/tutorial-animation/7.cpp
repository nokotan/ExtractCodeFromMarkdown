# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(Palette::White);

	int32 count = 0;

	while (System::Update())
	{
		// もし左クリックされたら
		if (MouseL.down())
		{
			++count;
		}

		Circle{ Scene::Center(), (count * 20) }.draw(ColorF{ 0.25 });
	}
}
