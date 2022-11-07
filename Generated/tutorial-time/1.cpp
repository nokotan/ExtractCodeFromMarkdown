# include <Siv3D.hpp>

void Main()
{
	Stopwatch stopwatch{ StartImmediately::Yes };

	while (System::Update())
	{
		ClearPrint();

		const String s = stopwatch.format();

		Print << s;

		Print << stopwatch;
	}
}
