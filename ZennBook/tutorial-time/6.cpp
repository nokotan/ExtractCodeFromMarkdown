# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		ClearPrint();
		Print << Time::GetSecSinceEpoch();
		Print << Time::GetMillisecSinceEpoch();
		Print << Time::GetMicrosecSinceEpoch();
		Print << Time::UTCOffsetMinutes();
	}
}
