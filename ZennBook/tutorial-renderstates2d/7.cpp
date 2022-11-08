# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	const Texture cat{ U"🐈"_emoji };

	while (System::Update())
	{
		const ScopedViewport2D viewport{ 400, 300, 400, 300 };

		Circle{ 200, 150, 200 }.draw();

		cat.draw(0, 0);
	}
}
