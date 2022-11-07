# include <Siv3D.hpp>

struct Item
{
	// アイテムのラベル
	String label;

	// アイテムの左上座標
	Point pos;
};

// 再帰的に TOML の要素を表示
void ShowTable(const TOMLValue& value)
{
	for (const auto& table : value.tableView())
	{
		switch (table.value.getType())
		{
		case TOMLValueType::Empty:
			Console << U"[Empty]" << table.name;
			break;
		case TOMLValueType::Table:
			Console << U"[Table]" << table.name;
			ShowTable(table.value);
			break;
		case TOMLValueType::Array:
			Console << U"[Array]" << table.name;
			for (const auto& element : table.value.arrayView())
			{
				switch (element.getType())
				{
				case TOMLValueType::String:
					Console << element.getString();
					break;
				case TOMLValueType::Number:
					Console << element.get<double>();
					break;
				case TOMLValueType::Bool:
					Console << element.get<bool>();
					break;
				case TOMLValueType::Date:
					Console << element.getDate();
					break;
				case TOMLValueType::DateTime:
					Console << element.getDateTime();
					break;
				default:
					break;
				}
			}
			break;
		case TOMLValueType::TableArray:
			Console << U"[TableArray]" << table.name;
			for (const auto& table2 : table.value.tableArrayView())
			{
				ShowTable(table2);
			}
			break;
		case TOMLValueType::String:
			Console << U"[String]" << table.name;
			Console << table.value.getString();
			break;
		case TOMLValueType::Number:
			Console << U"[Number]" << table.name;
			Console << table.value.get<double>();
			break;
		case TOMLValueType::Bool:
			Console << U"[Bool]" << table.name;
			Console << table.value.get<bool>();
			break;
		case TOMLValueType::Date:
			Console << U"[Date]" << table.name;
			Console << table.value.getDate();
			break;
		case TOMLValueType::DateTime:
			Console << U"[DateTime]" << table.name;
			Console << table.value.getDateTime();
			break;
		case TOMLValueType::Unknown:
			Console << U"[Unknown]" << table.name;
			break;
		}
	}
}

void Main()
{
	// TOML ファイルからデータを読み込む
	const TOMLReader toml{ U"example/toml/config.toml" };

	if (not toml) // もし読み込みに失敗したら
	{
		throw Error{ U"Failed to load `config.toml`" };
	}

	// TOML データをすべて表示
	ShowTable(toml);

	Console << U"-----";

	// 要素のパスで値を取得
	const String windowTitle = toml[U"Window.title"].getString();
	const int32 windowWidth = toml[U"Window.width"].get<int32>();
	const int32 windowHeight = toml[U"Window.height"].get<int32>();
	const bool windowSizable = toml[U"Window.sizable"].get<bool>();
	const ColorF sceneBackground = toml[U"Scene.background"].get<ColorF>();

	Window::SetTitle(windowTitle);
	Window::Resize(windowWidth, windowHeight);
	Window::SetStyle(windowSizable ? WindowStyle::Sizable : WindowStyle::Fixed);
	Scene::SetBackground(sceneBackground);

	// 数値の配列を TOML データから作成
	Array<int32> values;
	{
		for (const auto& object : toml[U"Array.values"].arrayView())
		{
			values << object.get<int32>();
		}
	}
	Console << values;

	// アイテムの配列を TOML データから作成
	Array<Item> items;
	{
		for (const auto& object : toml[U"Items"].tableArrayView())
		{
			Item item;
			item.label = object[U"label"].getString();
			item.pos = Point{ object[U"pos.x"].get<int32>(), object[U"pos.y"].get<int32>() };
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
