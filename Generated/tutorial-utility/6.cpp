# include <Siv3D.hpp>

void Main()
{
	for (auto p : step({ 2, 3 }))
	{
		Print << p;
	}

	Print << U"---";

	const Size size{ 2, 4 };

	for (auto p : step(size))
	{
		Print << p;
	}

	Print << U"---";

	const Grid grid{ {10, 20}, {30, 40} };

	for (auto p : step(grid.size()))
	{
		Print << grid[p];
	}

	while (System::Update())
	{

	}
}
