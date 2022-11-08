# include <Siv3D.hpp>

void Main()
{
	// IsOdd: 奇数であるか判定
	Print << IsOdd(1);
	Print << IsOdd(0);
	Print << IsOdd(-11);
	Print << IsOdd(9876543210ULL);

	// IsEven: 偶数であるか判定
	Print << IsEven(1);
	Print << IsEven(0);
	Print << IsEven(-11);
	Print << IsEven(9876543210ULL);

	while (System::Update())
	{

	}
}
