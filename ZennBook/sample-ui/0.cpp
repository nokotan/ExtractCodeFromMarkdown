# include <Siv3D.hpp>

void Main()
{
	const Point topleft{ 80, 60 };
	const double thickness = 3.0;
	double offset = 0.0;

	while (System::Update())
	{
		offset += (Scene::DeltaTime() * 10);

		const Rect rect{ topleft, Cursor::Pos() - topleft };
		rect.top().draw(LineStyle::SquareDot(offset), thickness);
		rect.right().draw(LineStyle::SquareDot(offset), thickness);
		rect.bottom().draw(LineStyle::SquareDot(offset), thickness);
		rect.left().draw(LineStyle::SquareDot(offset), thickness);
	}
}
