# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		const double t = (Scene::Time() * -30_deg);

		const Transformer2D t0{ Mat3x2::Translate(Scene::Center()) };
		Circle{ 0, 0, 40 }.draw(Palette::Orange);
		Circle{ 0, 0, 160 }.drawFrame(2);

		const Transformer2D t1{ Mat3x2::Translate(160, 0).rotated(t) };
		Circle{ 0, 0, 20 }.draw(Palette::Skyblue);
		Circle{ 0, 0, 40 }.drawFrame(2);

		const Transformer2D t2{ Mat3x2::Translate(40, 0).rotated(t * 4) };
		Circle{ 0, 0, 10 }.draw(Palette::Yellow);
	}
}
