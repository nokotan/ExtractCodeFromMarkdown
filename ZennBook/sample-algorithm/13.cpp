# include <Siv3D.hpp>

void Main()
{
	const Polygon star = Shape2D::Star(200, Scene::Center(), 15_deg);

	// 凸包を計算
	const Polygon convexHull = star.computeConvexHull();

	while (System::Update())
	{
		convexHull.draw(Palette::Gray);

		star.draw(Palette::Yellow);
	}
}
