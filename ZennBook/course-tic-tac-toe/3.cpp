# include <Siv3D.hpp>

class GameBoard
{
public:

	// セルの大きさ
	static constexpr int32 CellSize = 150;

	// O マークの値
	static constexpr int32 O_Mark = 1;

	// X マークの値
	static constexpr int32 X_Mark = 2;

	void update()
	{
		// 3x3 のセル
		for (auto p : step(Size{ 3, 3 }))
		{
			// セル
			const Rect cell{ (p * CellSize), CellSize };

			// セルのマーク
			const int32 mark = m_grid[p];

			// セルが空白で、なおかつクリックされたら
			if ((mark == 0) && cell.leftClicked())
			{
				// セルに現在のマークを書き込む
				m_grid[p] = m_currentMark;

				// 現在のマークを入れ替える
				m_currentMark = ((m_currentMark == O_Mark) ? X_Mark : O_Mark);
			}
		}
	}

	// 描画
	void draw() const
	{
		drawGridLines();

		drawCells();
	}

private:

	// 3x3 の二次元配列 (初期値は全要素 0)
	Grid<int32> m_grid = Grid<int32>(3, 3);

	// これから置くマーク
	int32 m_currentMark = O_Mark;

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

			// セルのマーク
			const int32 mark = m_grid[p];

			// X マークだったら
			if (mark == X_Mark)
			{
				// X マークを描く
				Shape2D::Cross(CellSize * 0.4, 10, cell.center())
					.draw(ColorF{ 0.2 });

				// このセルはこれ以上処理しない
				continue;
			}
			else if (mark == O_Mark) // O マークだったら
			{
				// 〇 マークを描く
				Circle{ cell.center(), (CellSize * 0.4 - 10) }
					.drawFrame(10, 0, ColorF{ 0.2 });

				// このセルはこれ以上処理しない
				continue;
			}

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
		gameBoard.update();

		gameBoard.draw();
	}
}
