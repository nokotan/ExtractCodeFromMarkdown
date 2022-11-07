# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		Circle{ 300, 300, 200 }
			.drawArc(270_deg, 30_deg, 40, 0);

		Circle{ 500, 300, 200 }		
			.drawArc(0_deg, 120_deg, 80, 0, Palette::Skyblue)
			.drawArc(120_deg, 70_deg, 0, 20, Palette::Orange);
	}
}
