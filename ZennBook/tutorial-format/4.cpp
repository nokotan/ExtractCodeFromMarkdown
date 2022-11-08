# include <Siv3D.hpp>

void Main()
{
	Print << U"{:0>5}"_fmt(3);
	Print << U"{:>5}"_fmt(3);

	Print << U"{:>6}"_fmt(100);
	Print << U"{:*>6}"_fmt(100);
	Print << U"{:<6}"_fmt(100);
	Print << U"{:*<6}"_fmt(100);
	Print << U"{:^6}"_fmt(100);
	Print << U"{:*^6}"_fmt(100);

	Print << U"{:?>6}"_fmt(U"aaa");
	Print << U"{:?>6}"_fmt(U"aaabbb");
	Print << U"{:?>6}"_fmt(U"aaabbbccc");

	while (System::Update())
	{

	}
}
