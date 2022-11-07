# include <Siv3D.hpp>

void Main()
{
	const Array<int32> coins =
	{
		1, 2, 5, 10, 20, 50, 100
	};

	while (System::Update())
	{
		if (SimpleGUI::Button(U"Reset", Vec2{ 200, 20 }))
		{
			ClearPrint();

			// ランダムな要素を 3 つ返す
			Print << coins.choice(3);
		}
	}
}
