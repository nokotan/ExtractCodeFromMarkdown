# include <Siv3D.hpp>

void Main()
{
	// 背景色を設定
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	// 文字列の配列
	const Array<String> items =
	{
		U"大吉", U"吉", U"中吉", U"小吉", U"末吉", U"凶"
	};

	// 抽選中である場合 true
	bool active = true;

	// 選ばれた文字列
	String currentItem;

	// メインループ
	while (System::Update())
	{
		// 抽選中である場合
		if (active)
		{
			// ランダムに 1 個選択
			currentItem = items.choice();
		}

		// (220, 100) の位置に幅 150 のボタンを表示
		// ボタンのラベルは currentItem
		if (SimpleGUI::Button(currentItem, Vec2{ 220, 100 }, 150))
		{
			// もし押されたら
			// active の状態を反転 (true → false, false → true)
			active = !active;
		}
	}
}
