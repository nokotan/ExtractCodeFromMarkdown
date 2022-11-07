# include <Siv3D.hpp>

void Main()
{
	// 現在の日付と時刻を取得
	const DateTime t = DateTime::Now();
	Print << t;
	Print << t.year;
	Print << t.month;
	Print << t.day;
	Print << t.hour;
	Print << t.minute;
	Print << t.second;
	Print << t.milliseconds;

	// 30 分前
	Print << (t - 30min);

	// 来週
	Print << (t + 7_d);

	// 2030 年まであと
	const Duration s = (DateTime{ 2030, 1, 1 } - t);
	Print << s;
	Print << DaysF{ s };
	Print << DurationCast<Days>(s);

	while (System::Update())
	{

	}
}
