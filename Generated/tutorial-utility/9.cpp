# include <Siv3D.hpp>

void Main()
{
	// 差の絶対値
	Print << AbsDiff(50, 10);
	Print << AbsDiff(10u, 50u);
	Print << AbsDiff(-2000000000, 2000000000);
	Print << AbsDiff(1.23, -1.23);

	while (System::Update())
	{

	}
}
