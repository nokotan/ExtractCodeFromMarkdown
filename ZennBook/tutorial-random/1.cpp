# include <Siv3D.hpp>

void Main()
{
	// シードを設定
	Reseed(123456789ull);

	for (int32 i = 0; i < 10; ++i)
	{
		Print << Random(100);
	}

	while (System::Update())
	{

	}
}
