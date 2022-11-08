# include <Siv3D.hpp>

void Main()
{
	// 0, 1, 2
	for (auto i : step(3))
	{
		Print << i;
	}

	Print << U"---";

	// 5, 6, 7, 8, 9, 10
	for (auto i : Range(5, 10))
	{
		Print << i;
	}

	Print << U"---";

	// 20, 18, 16, 14, 12, 10
	for (auto i : Range(20, 10, -2))
	{
		Print << i;
	}

	while (System::Update())
	{

	}
}
