# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 1.0, 0.96, 0.92 });
	Image image{ Scene::Size(), Palette::White };
	DynamicTexture texture{ image };

	while (System::Update())
	{
		ClearPrint();
		Print << U"IsAvailable: " << Pentablet::IsAvailable();
		Print << U"SupportsPressure: " << Pentablet::SupportsPressure();
		Print << U"SupportsTangentPressure: " << Pentablet::SupportsTangentPressure();
		Print << U"SupportsOrientation: " << Pentablet::SupportsOrientation();
		Print << U"Pressure: " << Pentablet::Pressure();
		Print << U"TangentPressure: " << Pentablet::TangentPressure();
		Print << U"Azimuth: " << Pentablet::Azimuth();
		Print << U"Altitude: " << Pentablet::Altitude();
		Print << U"Twist: " << Pentablet::Twist();

		if (MouseL.pressed())
		{
			const Point from = (MouseL.down() ? Cursor::Pos() : Cursor::PreviousPos());
			const Point to = Cursor::Pos();

			const double thickness = (Math::Square(Pentablet::Pressure()) * 40.0);
			Line{ from, to }.overwrite(image, static_cast<int32>(thickness), ColorF{ 0.1 });

			texture.fill(image);
		}

		texture.draw();
	}
}
