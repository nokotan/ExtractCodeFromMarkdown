# include <Siv3D.hpp>

void Main()
{
	// 現在の日付を取得
	const Date date = Date::Today();
	Print << date;
	Print << date.year;
	Print << date.month;
	Print << date.day;

	// 10 日前の日付
	Print << (date - 10_d);

	// 10 日後の日付
	Print << (date + 10_d);

	// 日付の引き算
	Print << (Date::Tomorrow() - Date::Yesterday());

	while (System::Update())
	{

	}
}
