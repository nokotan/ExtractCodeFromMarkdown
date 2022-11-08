# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		// 長方形の辺を X 軸方向に 30px ずつスライドさせた平行四辺形
		Rect{ 100, 50, 200, 100 }.drawFrame(1, 0)
			.shearedX(30).draw(Palette::Skyblue);

		// 長方形の辺を Y 軸方向に -50px ずつスライドさせた平行四辺形
		Rect{ 400, 150, 300, 200 }.drawFrame(1, 0)
			.shearedY(-50).draw(Palette::Orange);
	}
}
