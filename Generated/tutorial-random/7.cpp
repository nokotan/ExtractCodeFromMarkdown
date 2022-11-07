# include <Siv3D.hpp>

void Main()
{
	const Array<String> options =
	{
		U"Red", U"Green", U"Blue", U"Black", U"White"
	};

	while (System::Update())
	{
		if (SimpleGUI::Button(U"Reset", Vec2{ 200, 20 }))
		{
			ClearPrint();

			// ランダムな要素を返す
			Print << options.choice();
		}
	}
}
