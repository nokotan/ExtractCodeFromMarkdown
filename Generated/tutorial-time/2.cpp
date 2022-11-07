# include <Siv3D.hpp>

void Main()
{
	Stopwatch stopwatch{ StartImmediately::Yes };

	while (System::Update())
	{
		ClearPrint();
		Print << stopwatch;

		if (500ms <= stopwatch)
		{
			Print << U"500msec";
		}

		if (3s <= stopwatch)
		{
			Print << U"3sec";
		}

		if (5.5s <= stopwatch)
		{
			Print << U"5.5sec";
		}
	}
}
