# include <Siv3D.hpp>

void Main()
{
	// Line や Circle, Triangle, Quad も OK
	constexpr RectF shape{ 100, 100, 400, 300 };

	Array<Vec2> points;

	while (System::Update())
	{
		if (SimpleGUI::Button(U"Generate", Vec2{ 20, 20 }))
		{
			points.clear();

			for (int32 i = 0; i < 100; ++i)
			{
				// shape 内にあるランダムな点
				points << RandomVec2(shape);
			}
		}

		shape.draw(Palette::Gray);

		for (const auto& point : points)
		{
			Circle{ point, 3 }.draw();
		}
	}
}
