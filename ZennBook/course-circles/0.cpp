# include <Siv3D.hpp>

void Main()
{
	// 円の半径
	constexpr double circleR = 24.0;

	// 円の色
	constexpr ColorF circleColor{ 0.4, 0.8, 0.6 };

	// 円を格納する配列
	Array<Circle> circles;

	while (System::Update())
	{
		// もし左クリックされたら
		if (MouseL.down())
		{
			// 配列に円を追加
			circles << Circle{ Cursor::Pos(), circleR };
		}

		// 配列内の円を描画
		for (const auto& circle : circles)
		{
			circle.draw(circleColor);
		}
	}
}
