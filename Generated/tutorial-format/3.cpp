# include <Siv3D.hpp>

void Main()
{
	Print << U"{}"_fmt(Math::Pi);

	Print << U"{:.3f}"_fmt(Math::Pi);

	// インデックス指定と組み合わせる場合、インデックス値は : の左
	Print << U"{1} ≒ {0:.6f}"_fmt(Math::Pi, U"π");

	Print << U"{}"_fmt(12345.678);

	Print << U"{:.3f}"_fmt(12345.678);

	Print << U"{:.6f}"_fmt(12345.678);

	Print << U"{}"_fmt(9876543.21);

	Print << U"{:.0f}"_fmt(9876543.21);

    // Vec2 型にも使える
	Print << U"{}"_fmt(Vec2{ 1.111, 2.222 });
	Print << U"{:.1f}"_fmt(Vec2{ 1.111, 2.222 });

	while (System::Update())
	{

	}
}
