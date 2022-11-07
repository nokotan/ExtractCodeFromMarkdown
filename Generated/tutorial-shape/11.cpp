# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		// 4 つの頂点座標を指定して四角形を描く
		Quad{ Vec2{ 100, 100 }, Vec2{ 150, 100 }, Vec2{ 300, 300 }, Vec2{ 100, 300 } }.draw();

		Quad{ Vec2{ 300, 400 }, Vec2{ 500, 100 }, Vec2{ 600, 200 }, Vec2{ 500, 500 } }.draw(Palette::Skyblue);
	}
}
