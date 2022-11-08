# include <Siv3D.hpp>

void Main()
{
	Image image{ 600, 600, Palette::White };

	Circle{ 100, 100, 100 }.overwrite(image, Palette::Orange);

	Rect{ 150, 150, 300, 200 }.paint(image, ColorF{ 0.0, 1.0, 0.5, 0.5 });

	Line{ 100, 400, 400, 200 }.overwrite(image, 10, Palette::Seagreen);

	// Shape2D には .paint() / .overwrite() が無いので、.asPolygon() で Polygon 型にする
	Shape2D::Star(200, Vec2{ 500, 200 }).asPolygon().overwrite(image, Palette::Yellow);

	// 透明の穴をあける
	Rect{ 400, 400, 50 }.overwrite(image, ColorF{ 1.0, 0.0 });

	image.save(U"tutorial2.png");

	const Texture texture{ image };

	while (System::Update())
	{
		texture.draw();
	}
}
