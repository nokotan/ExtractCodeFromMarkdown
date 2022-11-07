# include <Siv3D.hpp>

void Main()
{
	// 軽量な乱数エンジン
	SmallRNG rng1{ 123456789ull };

	for (int32 i = 0; i < 10; ++i)
	{
		Print << Random(1, 6, rng1);
	}

	while (System::Update())
	{

	}
}
