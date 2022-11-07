# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });
	const Font font{ 30 };
	font.preload(U"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.,!?0123456789");

	while (System::Update())
	{
		font(U"Hello, Siv3D!").draw(20, 20, ColorF{ 0.25 });

		font.getTexture().draw(20, 100);
	}
}
