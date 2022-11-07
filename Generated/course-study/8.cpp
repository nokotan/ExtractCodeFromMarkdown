# include <Siv3D.hpp>

void Main()
{
	int32 count = 0;

	while (System::Update())
	{
		// Print したメッセージを消去
		ClearPrint();

		Print << count;

		++count;
	}
}
