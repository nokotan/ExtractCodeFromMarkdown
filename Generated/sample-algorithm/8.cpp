# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	LineString points;
	Polygon polygon;

	double distanceFromOrigin = 0.0;
	double length = 0.0;

	while (System::Update())
	{
		if (MouseL.down())
		{
			points << Cursor::Pos();
			polygon = points.calculateRoundBuffer(20);
			length = points.calculateLength();
		}

		polygon.draw().drawFrame(2, ColorF{ 0.7 });
		points.draw(2, ColorF{ 0.75 });

		if (2 < points.size() && length)
		{
			distanceFromOrigin += (Scene::DeltaTime() * 800);

			if (length < distanceFromOrigin)
			{
				distanceFromOrigin = Math::Fmod(distanceFromOrigin, length);
			}

			const Vec2 position = points.calculatePointFromOrigin(distanceFromOrigin);
			position.asCircle(20).draw(ColorF{ 0.5 });
		}
	}
}
