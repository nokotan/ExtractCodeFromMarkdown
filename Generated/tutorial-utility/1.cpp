# include <Siv3D.hpp>

void Main()
{
	Print << Clamp(10, 0, 100);
	Print << Clamp(-10, 0, 100);
	Print << Clamp(110, 0, 100);

	Print << Clamp(9.99, -1.0, 1.0);
	Print << Clamp(-9.99, -1.0, 1.0);
	Print << Clamp(0.0, -1.0, 1.0);

	while (System::Update())
	{

	}
}
