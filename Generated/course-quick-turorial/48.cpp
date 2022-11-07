# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		ClearPrint();
		Print << KeyA.pressedDuration();

		if (1s <= KeySpace.pressedDuration())
		{
			Print << U"Space";
		}
	}
}
