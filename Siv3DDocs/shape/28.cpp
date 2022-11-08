# include <Siv3D.hpp>

void Main()
{
	const Polygon star = Shape2D::Star(150, Vec2{ 0, 0 });

	while (System::Update())
	{
		star.scaled(1.2).movedBy(200, 200).draw(ColorF{ 0.6 });

		star.movedBy(200, 200).draw(ColorF{ 0.8 });

		star.scaled(0.8).movedBy(200, 200).draw(ColorF{ 1.0 });


		star.rotated(-30_deg).movedBy(600, 400).draw(ColorF{ 0.6 });

		star.movedBy(600, 400).draw(ColorF{ 0.8 });

		star.rotated(30_deg).movedBy(600, 400).draw(ColorF{ 1.0 });
	}
}
