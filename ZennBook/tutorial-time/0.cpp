# include <Siv3D.hpp>

void Main()
{
	const Hours t0 = 3h + 2h;
	Print << t0;
	Print << t0.count(); // 数値型として値を取得するには .count()

	const MinutesF t1 = 1h + 30min + 180s;
	Print << t1;
	Print << t1.count();

	const Duration t2 = 10min + 5.5s;
	Print << t2;
	Print << t2.count();

	while (System::Update())
	{

	}
}
