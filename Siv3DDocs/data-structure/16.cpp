# include <Siv3D.hpp>

void Main()
{
	Grid<double> grid =
	{
		{ 0.1, 0.2, 0.3, 0.4, 0.5, 0.6 },
		{ 1.0, 0.95, 0.9, 0.85, 0.8, 0.75 }
	};

	// グリッドのサイズ Size{ 幅, 高さ } 
	Print << grid.size();

	// グリッドの幅
	Print << U"width: " << grid.width();

	// グリッドの高さ（行数）
	Print << U"height: " << grid.height();

	// 0 行目 0 番目の要素にアクセス
	Print << grid[0][0];

	// 0 行目 1 番目の要素にアクセス
	Print << grid[0][1];

	// 1 行目 5 番目の要素にアクセス
	Print << grid[1][5];

	// 1 行目 5 番目の要素にアクセス (X と Y の順番に注意)
	Print << grid[Point{ 5, 1 }];

	while (System::Update())
	{
		for (auto y : step(grid.height()))
		{
			for (auto x : step(grid.width()))
			{
				Rect{ (x * 100), (y * 100), 100 }.draw(ColorF{ grid[y][x] });
			}
		}
	}
}
