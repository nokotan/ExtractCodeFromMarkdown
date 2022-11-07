# include <Siv3D.hpp>

void Main()
{
	const Polygon star = Shape2D::Star(200, Scene::Center());

	while (System::Update())
	{
		const Rect rect{ Arg::center = Cursor::Pos(), 300, 100 };

		star.drawFrame(2, Palette::Yellow);

		rect.draw(ColorF{ 1.0, 0.8 });

		// star と rect の重なる領域を Polygon の配列で取得
		for (const auto& polygon : Geometry2D::And(star, rect))
		{
			polygon.draw(ColorF{ 1.0, 0.0, 0.0, 0.5 })
				.drawFrame(4, ColorF{ 1.0, 0.0, 0.0 });
		}
	}
}
