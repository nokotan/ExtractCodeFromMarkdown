# include <Siv3D.hpp>

void DrawStickyNote(const RectF& rect, const ColorF& noteColor)
{
	// 少しだけ回転させて影を描く
	{
		const Transformer2D t{ Mat3x2::Rotate(2_deg, rect.pos) };

		rect.stretched(-2, 1, 1, -4).drawShadow(Vec2{ 0, 0 }, 12, 0, ColorF{ 0.0, 0.4 });
	}

	rect.draw(noteColor);
}

void Main()
{
	Scene::SetBackground(ColorF{ 1.0, 0.98, 0.96 });

	const Font font{ 36, Typeface::Bold };

	while (System::Update())
	{
		for (auto i : step(10))
		{
			const RectF rect{ (60 + i / 5 * 280), (20 + i % 5 * 90), 230, 70 };

			DrawStickyNote(rect, HSV{ (i * 36), 0.46, 1.0 });

			font(U"Text").draw(rect.pos.movedBy(20, 10), ColorF{ 0.1, 0.95 });
		}
	}
}
