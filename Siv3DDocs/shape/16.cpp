# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		// 中心 (300, 200), X 軸方向の半径 200, Y 軸方向の半径　100 の楕円
		Ellipse{ 300, 200, 200, 100 }.draw(Palette::Skyblue);

		// 中心 (600, 400), X 軸方向の半径 50, Y 軸方向の半径　150 の楕円
		Ellipse{ 600, 400, 50, 150 }.draw(Palette::Orange);
	}
}
