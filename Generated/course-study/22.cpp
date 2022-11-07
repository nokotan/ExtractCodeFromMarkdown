# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		const double angle = (Scene::Time() * 60_deg);

		Line{ 20, 20, 80, 80 }.draw(4);
		Rect{ 120, 40, 60, 40 }.draw();
		Circle{ 250, 50, 30 }.draw();
		Ellipse{ 350, 50, 30, 20 }.draw();	
		Triangle{ 450, 60, 70, angle }.draw();
		Quad{ {520, 20}, {580, 40}, {580, 80}, {520, 80} }.draw();
		RoundRect{ 620, 20, 80, 60, 10 }.draw();
		Rect{ 720, 30, 60, 40 }.rounded(20, 0, 20, 0).draw();

		Rect{ 20, 130, 60, 40 }.rotated(angle).draw();
		Polygon{ {120, 120}, {150, 110}, {180, 150}, {150, 140}, {120, 180} }.draw();
		Bezier2{ {220, 180}, {250, 100}, {280, 120} }.draw(3);
		Bezier3{ {320, 180}, {350, 180}, {350, 120}, {380, 120} }.draw(3);
		LineString{ {420, 180}, {450, 120}, {460, 180}, {480, 120} }.draw(3);
		LineString{ {520, 180}, {540, 150}, {560, 160}, {580, 120} }.asSpline().draw(3);
		Shape2D::Plus(40, 20, { 650, 150 }, angle).draw();
		Shape2D::Cross(40, 15, { 750, 150 }, angle).draw();

		Shape2D::Pentagon(40, { 50, 250 }, angle).draw();
		Shape2D::Hexagon(40, { 150, 250 }, angle).draw();
		Shape2D::Ngon(8, 40, { 250, 250 }, angle).draw();
		Shape2D::Star(40, { 350, 250 }, angle).draw();
		Shape2D::NStar(8, 40, 30, { 450, 250 }, angle).draw();
		Line{ 520, 220, 580, 280 }.drawArrow(4, { 20, 30 });
		Shape2D::Rhombus(60, 40, { 650, 250 }, angle).draw();
		Shape2D::RectBalloon(Rect{ 720, 220, 60, 40 }, { 710, 290 }).draw();

		Shape2D::Stairs({ 80, 380 }, 60, 60, 4).draw();
		Shape2D::Heart(40, { 150, 350 }, angle).draw();
		Shape2D::Hexagon(40, { 250, 350 })
			.asPolygon().addHole({ {260, 340}, {240, 340}, {240, 360}, {260, 360} }).draw();
		Rect{ 320, 320, 60, 60 }.drawFrame(5);
		Circle{ 450, 350, 40 }.drawFrame(5);
		Circle{ 550, 350, 40 }.drawPie(angle, 120_deg);
		Circle{ 650, 350, 40 }.drawArc(angle, 240_deg, 10, 0);
		Circle{ 750, 350, 40 }.drawArc(LineStyle::RoundCap, angle, 240_deg, 10, 0);

		Line{ 20, 420, 80, 480 }.draw(LineStyle::RoundCap, 6);
		Line{ 120, 420, 180, 480 }.draw(LineStyle::SquareDot, 6);
		Line{ 220, 420, 280, 480 }.draw(LineStyle::RoundDot, 6);
	}
}
