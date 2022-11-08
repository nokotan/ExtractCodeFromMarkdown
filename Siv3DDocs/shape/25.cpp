# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		// 開始角度 270° から 30° の大きさの扇形を描く
		Circle{ 300, 300, 200 }
			.drawPie(270_deg, 30_deg);

		// 開始角度 0° から 120° の大きさの扇形と
		// 開始角度 120° から 70° の大きさの扇形を描く
		Circle{ 500, 300, 200 }
			.drawPie(0_deg, 120_deg, Palette::Skyblue)
			.drawPie(120_deg, 70_deg, Palette::Orange);
	}
}
