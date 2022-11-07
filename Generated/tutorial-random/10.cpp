# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		if (SimpleGUI::Button(U"Reset", Vec2{ 200, 20 }))
		{
			ClearPrint();

			// ランダムに選択
			Print << Sample({ 1, 2, 5, 10, 20, 50, 100 });
		}
	}
}
