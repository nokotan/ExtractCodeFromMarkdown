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
	// INI ファイルからデータを読み込む
	const INI ini{ U"example/ini/config.ini" };

	if (not ini) // もし読み込みに失敗したら
	{
		throw Error{ U"Failed to load `config.ini`" };
	}

	// 全てのセクションを列挙
	for (const auto& section : ini.sections())
	{
		// セクション名
		Print << U"[{}]"_fmt(section.section);

		// セクション内のすべてのキーを列挙
		for (const auto& key : section.keys)
		{
			// キーの名前と値
			Print << U"{} = {}"_fmt(key.name, key.value);
		}
	}
	Print << U"-----";

	// Windows セクションの title キーの値（テキスト）を取得
	const String windowTitle = ini[U"Window.title"];

	// Windows セクションの width キーの値（テキスト）を int32 型の値に変換
	const int32 windowWidth = Parse<int32>(ini[U"Window.width"]);

	// Windows セクションの height キーの値（テキスト）を int32 型の値に変換
	const int32 windowHeight = Parse<int32>(ini[U"Window.height"]);

	// Windows セクションの sizable キーの値（テキスト）を bool 型の値に変換
	const bool windowSizable = Parse<bool>(ini[U"Window.sizable"]);

	// Scene セクションの background キーの値（テキスト）を ColorF 型の値に変換
	const ColorF sceneBackground = Parse<ColorF>(ini[U"Scene.background"]);

	Window::SetTitle(windowTitle);
	Window::Resize(windowWidth, windowHeight);
	Window::SetStyle(windowSizable ? WindowStyle::Sizable : WindowStyle::Fixed);
	Scene::SetBackground(sceneBackground);

	// Array セクションの values キーの値（テキスト）を ',' で区切って配列にし、それぞれの要素を int32 型の値に変換
	Array<int32> values = ini[U"Array.values"].split(U',').map(Parse<int32>);
	Print << values;

	// アイテムの配列を INI データから作成
	Array<Item> items;
	{
		const size_t itemsCount = Parse<size_t>(ini[U"Items.count"]);

		for (auto i : step(itemsCount))
		{
			Item item;
			item.label = ini[U"Item{}.label"_fmt(i)];
			item.pos = Parse<Point>(ini[U"Item{}.pos"_fmt(i)]);
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
