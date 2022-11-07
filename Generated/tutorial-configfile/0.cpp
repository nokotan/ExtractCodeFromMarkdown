# include <Siv3D.hpp>

struct Item
{
	// アイテムのラベル
	String label;

	// アイテムの左上座標
	Point pos;
};

void Main()
{
	// CSV ファイルからデータを読み込む
	const CSV csv{ U"example/csv/config.csv" };

	if (not csv) // もし読み込みに失敗したら
	{
		throw Error{ U"Failed to load `config.csv`" };
	}

	// 全ての行を列挙
	for (size_t row = 0; row < csv.rows(); ++row)
	{
		// 行 (Array<String>) の要素を表示
		Print << csv[row];
	}
	Print << U"-----";

	// 1 行 1 列目のテキストを取得 (0 行, 0 列からカウント）
	const String windowTitle = csv[1][1];

	// 2 行 1 列目のテキストを int32 型の値に変換
	const int32 windowWidth = Parse<int32>(csv[2][1]);

	// 3 行 1 列目のテキストを int32 型の値に変換
	const int32 windowHeight = Parse<int32>(csv[3][1]);

	// 4 行 1 列目のテキストを bool 型の値に変換
	const bool windowSizable = Parse<bool>(csv[4][1]);

	// 5 行 1 列目のテキストを ColorF 型の値に変換
	const ColorF sceneBackground = Parse<ColorF>(csv[5][1]);

	Window::SetTitle(windowTitle);
	Window::Resize(windowWidth, windowHeight);
	Window::SetStyle(windowSizable ? WindowStyle::Sizable : WindowStyle::Fixed);
	Scene::SetBackground(sceneBackground);

	// 6 行 1 列目のテキストを ',' で区切って配列にし、それぞれの要素を int32 型の値に変換
	Array<int32> values = csv[6][1].split(U',').map(Parse<int32>);
	Print << values;

	// アイテムの配列を CSV データから作成
	Array<Item> items;
	{
		const size_t itemsCount = Parse<size_t>(csv[7][1]);
		const size_t baseLine = 8;

		for (auto i : step(itemsCount))
		{
			Item item;
			item.label = csv[baseLine + i * 2][1];
			item.pos = Parse<Point>(csv[baseLine + i * 2 + 1][1]);
			items << item;
		}
	}

	// アイテム描画用のフォント
	const Font font{ 30, Typeface::Bold };

	while (System::Update())
	{
		// アイテムを描画
		for (const auto& item : items)
		{
			const Rect rect{ item.pos, 180, 80 };

			rect.draw();

			font(item.label).drawAt(rect.center(), ColorF{ 0.25 });
		}
	}
}
