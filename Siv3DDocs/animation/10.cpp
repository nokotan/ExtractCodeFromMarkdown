# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(Palette::White);

	while (System::Update())
	{
		const double p0 = Periodic::Square0_1(2s);
		const double p1 = Periodic::Triangle0_1(2s);
		const double p2 = Periodic::Sine0_1(2s);
		const double p3 = Periodic::Sawtooth0_1(2s);
		const double p4 = Periodic::Jump0_1(2s);

		Line{ 100, 0, 100, 600 }.draw(2, ColorF{ 0.8 });
		Line{ 700, 0, 700, 600 }.draw(2, ColorF{ 0.8 });

		Circle{ 100 + p0 * 600, 100, 20 }.draw(ColorF{ 0.25 });
		Circle{ 100 + p1 * 600, 200, 20 }.draw(ColorF{ 0.25 });
		Circle{ 100 + p2 * 600, 300, 20 }.draw(ColorF{ 0.25 });
		Circle{ 100 + p3 * 600, 400, 20 }.draw(ColorF{ 0.25 });
		Circle{ 100 + p4 * 600, 500, 20 }.draw(ColorF{ 0.25 });
	}
}
