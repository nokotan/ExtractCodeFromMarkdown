# include <Siv3D.hpp>

void Main()
{
	// 5 列 x 3 行のグリッド（幅が 5, 高さが 3)
	// 要素の値はすべて -1
	Grid<int32> grid(5, 3, -1);

	Print << grid;

	Print << U"----";

	grid[2][0] = 123;

	Print << grid;

	while (System::Update())
	{

	}
}
