# include <Siv3D.hpp>

void Main()
{
	Array<String> cities =
	{
		U"Guangzhou", U"Tokyo", U"Shanghai", U"Jakarta",
		U"Delhi", U"Metro Manila", U"Mumbai", U"Seoul",
		U"Mexico City", U"São Paulo", U"New York City", U"Cairo",
	};

	while (System::Update())
	{
		if (SimpleGUI::Button(U"Shuffle", Vec2{ 200, 100 }))
		{
			ClearPrint();

			// 要素の順番をシャッフル
			cities.shuffle();

			Print << cities;
		}
	}
}
