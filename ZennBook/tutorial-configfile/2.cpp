# include <Siv3D.hpp>

struct Item
{
	// アイテムのラベル
	String label;

	// アイテムの左上座標
	Point pos;
};

// 再帰的に JSON の要素を表示
void ShowObject(const JSON& value)
{
	switch (value.getType())
	{
	case JSONValueType::Empty:
		Console << U"empty";
		break;
	case JSONValueType::Null:
		Console << U"null";
		break;
	case JSONValueType::Object:
		for (const auto& object : value)
		{
			Console << U"[" << object.key << U"]";
			ShowObject(object.value);
		}
		break;
	case JSONValueType::Array:
		for (const auto& element : value.arrayView())
		{
			ShowObject(element);
		}
		break;
	case JSONValueType::String:
		Console << value.getString();
		break;
	case JSONValueType::Number:
		Console << value.get<double>();
		break;
	case JSONValueType::Bool:
		Console << value.get<bool>();
		break;
	}
}

void Main()
{
	// JSON ファイルからデータを読み込む
	const JSON json = JSON::Load(U"example/json/config.json");

	if (not json) // もし読み込みに失敗したら
	{
		throw Error{ U"Failed to load `config.json`" };
	}

	// JSON データをすべて表示
	ShowObject(json);

	Console << U"-----";

	// 要素のパスで値を取得
	const String windowTitle = json[U"Window"][U"title"].getString();
	const int32 windowWidth = json[U"Window"][U"width"].get<int32>();
	const int32 windowHeight = json[U"Window"][U"height"].get<int32>();
	const bool windowSizable = json[U"Window"][U"sizable"].get<bool>();
	const ColorF sceneBackground = json[U"Scene"][U"background"].get<ColorF>();

	Window::SetTitle(windowTitle);
	Window::Resize(windowWidth, windowHeight);
	Window::SetStyle(windowSizable ? WindowStyle::Sizable : WindowStyle::Fixed);
	Scene::SetBackground(sceneBackground);

	// 数値の配列を JSON データから作成
	Array<int32> values;
	{
		for (const auto& object : json[U"Array"][U"values"].arrayView())
		{
			values << object.get<int32>();
		}
	}
	Console << values;

	// アイテムの配列を JSON データから作成
	Array<Item> items;
	{
		for (const auto& object : json[U"Items"].arrayView())
		{
			Item item;
			item.label = object[U"label"].getString();
			item.pos = Point{ object[U"pos"][U"x"].get<int32>(), object[U"pos"][U"y"].get<int32>() };
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
