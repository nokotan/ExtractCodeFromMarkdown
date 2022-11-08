# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		// 開始角度 270° から 30° の大きさの円弧を描く
		Circle{ 300, 300, 200 }
			.drawArc(270_deg, 30_deg, 40, 0);

		// 開始角度 0° から 120° の大きさの円弧と
		// 開始角度 120° から 70° の大きさの円弧を描く
		Circle{ 500, 300, 200 }		
			.drawArc(0_deg, 120_deg, 80, 0, Palette::Skyblue)
			.drawArc(120_deg, 70_deg, 0, 20, Palette::Orange);
	}
}
