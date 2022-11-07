# include <Siv3D.hpp>

void Main()
{
	Print << InRange(10, 0, 100);
	Print << InRange(-10, 0, 100);
	Print << InRange(110, 0, 100);

	Print << InRange(9.99, -1.0, 1.0);
	Print << InRange(-9.99, -1.0, 1.0);
	Print << InRange(0.0, -1.0, 1.0);

	while (System::Update())
	{

	}
}
