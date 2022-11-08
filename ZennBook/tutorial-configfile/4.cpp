# include <Siv3D.hpp>

struct Item
{
	// アイテムのラベル
	String label;

	// アイテムの左上座標
	Point pos;
};

// 再帰的に XML の要素を表示
void ShowElements(const XMLElement& element)
{
	for (auto e = element.firstChild(); e; e = e.nextSibling())
	{
		Console << U"<{}>"_fmt(e.name());

		if (const auto attributes = e.attributes())
		{
			Console << attributes;
		}

		if (const auto text = e.text())
		{
			Console << text;
		}

		ShowElements(e);

		Console << U"</{}>"_fmt(e.name());
	}
}

void Main()
{
	// XML ファイルからデータを読み込む
	const XMLReader xml(U"example/xml/config.xml");

	if (not xml) // もし読み込みに失敗したら
	{
		throw Error{ U"Failed to load `config.xml`" };
	}

	// XML データをすべて表示
	ShowElements(xml);

	Console << U"-----";

	String windowTitle;
	int32 windowWidth = Window::DefaultClientSize.x;
	int32 windowHeight = Window::DefaultClientSize.y;
	bool windowSizable = false;
	ColorF sceneBackground{ 0.0 };
	Array<int32> values;
	Array<Item> items;

	// 要素を走査して目的の値を取得
	for (auto elem = xml.firstChild(); elem; elem = elem.nextSibling())
	{
		const String name = elem.name();

		if (name == U"Window")
		{
			for (auto elem2 = elem.firstChild(); elem2; elem2 = elem2.nextSibling())
			{
				const String name2 = elem2.name();

				if (name2 == U"title")
				{
					windowTitle = elem2.text();
				}
				else if (name2 == U"width")
				{
					windowWidth = Parse<int32>(elem2.text());
				}
				else if (name2 == U"height")
				{
					windowHeight = Parse<int32>(elem2.text());
				}
				else if (name2 == U"sizable")
				{
					windowSizable = Parse<bool>(elem2.text());
				}
			}
		}
		else if (name == U"Scene")
		{
			for (auto elem2 = elem.firstChild(); elem2; elem2 = elem2.nextSibling())
			{
				const String name2 = elem2.name();

				if (name2 == U"background")
				{
					sceneBackground = Parse<ColorF>(elem2.text());
				}
			}
		}
		if (name == U"Array")
		{
			for (auto elem2 = elem.firstChild(); elem2; elem2 = elem2.nextSibling())
			{
				values << Parse<int32>(elem2.text());
			}
		}
		if (name == U"Items")
		{
			Item item;

			for (auto elem2 = elem.firstChild(); elem2; elem2 = elem2.nextSibling())
			{
				const String name2 = elem2.name();

				if (name2 == U"label")
				{
					item.label = elem2.text();
				}
				else if (name2 == U"pos")
				{
					Point pos{ 0, 0 };

					for (auto elem3 = elem2.firstChild(); elem3; elem3 = elem3.nextSibling())
					{
						const String name3 = elem3.name();

						if (name3 == U"x")
						{
							pos.x = Parse<int32>(elem3.text());
						}
						else if (name3 == U"y")
						{
							pos.y = Parse<int32>(elem3.text());
						}
					}

					item.pos = pos;
				}
			}

			items << item;
		}
	}

	Window::SetTitle(windowTitle);
	Window::Resize(windowWidth, windowHeight);
	Window::SetStyle(windowSizable ? WindowStyle::Sizable : WindowStyle::Fixed);
	Scene::SetBackground(sceneBackground);

	Console << values;

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
