# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });
	const Texture food{ U"🍿"_emoji };
	const Texture chick{ U"🐥"_emoji };

	while (System::Update())
	{
		Circle{ Scene::Center(), 100 }.draw();
		food.drawAt(Scene::Center());
		chick.drawAt(Cursor::Pos());
	}
}
