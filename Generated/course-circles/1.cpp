# include <Siv3D.hpp>

void Main()
{
	// 円の半径
	constexpr double circleR = 24.0;

	// 円の色
	constexpr ColorF circleColor{ 0.4, 0.8, 0.6 };

	// 円の中心座標を格納する配列
	Array<Vec2> circles;

	while (System::Update())
	{
		// もし左クリックされたら
		if (MouseL.down())
		{
			// 配列に円の中心座標を追加
			circles << Cursor::Pos();
		}

		// 配列内の円の中心座標を使って円を描画
		for (const auto& circle : circles)
		{
			Circle{ circle, circleR }.draw(circleColor);
		}
	}
}
