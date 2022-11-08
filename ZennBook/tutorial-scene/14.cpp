# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		ClearPrint();
		Print << System::GetCurrentMonitorIndex();
	}
}
