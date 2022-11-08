# include <Siv3D.hpp>

void Main()
{
	// 背景色を水色に
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	// 距離の表示用フォント
	const Font font{ 18, Typeface::Bold };

	// 迷路を可視化するときのマスのサイズ（ピクセル）
	constexpr int32 CellSize = 40;

	// 二次元配列: 迷路 (0: 通行可能, 1: 壁)
	const Grid<int32> maze =
	{
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1 },
		{ 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1 },
		{ 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1 },
		{ 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1 },
		{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	};

	// 無限大を表現する数
	constexpr int32 INF = 10000;

	// 二次元配列: maze と同じサイズ、すべての要素を INF にセット
	Grid<int32> distances(maze.size(), INF);

	while (System::Update())
	{
		// 状態更新フラグ
		bool update = false;

		// 迷路の状態を可視化
		for (int32 y = 0; y < maze.height(); ++y)
		{
			for (int32 x = 0; x < maze.width(); ++x)
			{
				// マスの正方形
				const Rect rect = Rect{ (x * CellSize), (y * CellSize), CellSize }.stretched(-1);

				if (maze[y][x] == 1) // 壁のマス
				{
					// 黒で表示
					rect.draw(ColorF{ 0.25 });
				}
				else // 通行可能なマス
				{
					// 距離情報
					const int32 distance = distances[y][x];

					if (distance == INF)
					{
						// 灰色で表示
						rect.draw(ColorF{ 0.75 });

						font(U"∞").drawAt(rect.center(), ColorF{0.25});
					}
					else
					{
						// 白で表示
						rect.draw();

						font(distances[y][x]).drawAt(rect.center(), ColorF{ 0.25 });
					}
				}
			}
		}
	}
}
