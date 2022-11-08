# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.7, 0.9, 0.8 });

	const Font font{ 100, Typeface::Bold };

	constexpr Vec2 center{ 400, 150 };

	const String text = U"Hello, Siv3D!";

	while (System::Update())
	{
		// center から (4, 4) ずらした位置を中心にテキストを描く
		font(text).drawAt(center.movedBy(4, 4), ColorF{ 0.0, 0.5 });

		// center を中心にテキストを描く
		font(text).drawAt(center);
	}
}
