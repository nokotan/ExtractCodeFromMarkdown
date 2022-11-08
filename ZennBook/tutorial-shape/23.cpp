# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		Circle{ 300, 300, 200 }
			.drawPie(270_deg, 30_deg);

		Circle{ 500, 300, 200 }
			.drawPie(0_deg, 120_deg, Palette::Skyblue)
			.drawPie(120_deg, 70_deg, Palette::Orange);
	}
}
