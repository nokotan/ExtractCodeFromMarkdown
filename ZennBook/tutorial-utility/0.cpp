# include <Siv3D.hpp>

void Main()
{
	const Array<int32> v = { 10, 20, 30 };

	Print << Max(100, 200);
	Print << Max(1.234, -3.456);
	Print << Max<size_t>(v.size(), 10);
	Print << Max({ 11, 44, 22, 55, 33 });

	Print << Min(100, 200);
	Print << Min(1.234, -3.456);
	Print << Min<size_t>(v.size(), 10);
	Print << Min({ 11, 44, 22, 55, 33 });

	while (System::Update())
	{

	}
}
