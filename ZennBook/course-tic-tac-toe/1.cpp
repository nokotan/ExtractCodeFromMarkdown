# include <Siv3D.hpp>

class GameBoard
{
public:

	// セルの大きさ
	static constexpr int32 CellSize = 150;

	// 描画
	void draw() const
	{
		drawGridLines();

		drawCells();
	}

private:

	// 格子を描く
	void drawGridLines() const
	{
		// 線を引く
		for (auto i : { 1, 2 })
		{
			Line{ (i * CellSize), 0, (i * CellSize), (3 * CellSize) }
				.draw(4, ColorF{ 0.25 });

			Line{ 0, (i * CellSize), (3 * CellSize), (i * CellSize) }
				.draw(4, ColorF{ 0.25 });
		}
	}

	// セルを描く
	void drawCells() const
	{
		// 3x3 のセル
		for (auto p : step(Size{ 3, 3 }))
		{
			// セル
			const Rect cell{ (p * CellSize), CellSize };

			// セルがマウスオーバーされたら
			if (cell.mouseOver())
			{
				// カーソルを手のアイコンに
				Cursor::RequestStyle(CursorStyle::Hand);

				// セルの上に半透明の白を描く
				cell.stretched(-2).draw(ColorF{ 1.0, 0.6 });
			}
		}
	}
};

void Main()
{
	// 背景色
	Scene::SetBackground(ColorF{ 0.8, 1.0, 0.9 });

	GameBoard gameBoard;

	while (System::Update())
	{
		gameBoard.draw();
	}
}
