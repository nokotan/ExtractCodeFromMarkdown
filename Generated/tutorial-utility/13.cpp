# include <Siv3D.hpp>

void Main()
{
	Array<int32> v = { 10,20,30,40,50 };

	Print << v;

	// コンソール出力
	Console << v;

	Console << U"Hello, Siv3D!";

	while (System::Update())
	{

	}
}
