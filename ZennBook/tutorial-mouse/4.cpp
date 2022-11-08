# include <Siv3D.hpp>

void Main()
{
    while (System::Update())
    {
        ClearPrint();
        Print << MouseL.pressedDuration();
		Print << MouseM.pressedDuration();
		Print << MouseR.pressedDuration();
    }
}
