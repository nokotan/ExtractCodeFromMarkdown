# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);
	Scene::SetBackground(ColorF{ 0.8, 0.9, 0.8 });

	Array<Vec2> points;
	Polygon polygon;
	LineString path;

	constexpr NavMeshConfig config{ .agentRadius = 20.0 };
	NavMesh navMesh;

	while (System::Update())
	{
		if (MouseL.down())
		{
			points << Cursor::Pos();
			polygon = Spline2D{ points }.calculateRoundBuffer(24, 8, 12);
			navMesh.build(polygon, config);
			path = navMesh.query(points.front(), points.back());
		}

		polygon.draw(ColorF{ 1.0 }).drawFrame(2, ColorF{ 0.7 });

		if (path)
		{
			path.draw(8, ColorF{ 0.1, 0.5, 0.9 });
			path.front().asCircle(12).draw(ColorF{ 1.0, 0.3, 0.0 });
			path.back().asCircle(12).draw(ColorF{ 1.0, 0.3, 0.0 });
		}
	}
}
