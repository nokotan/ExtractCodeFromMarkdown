# include <Siv3D.hpp>

void Main()
{
	Print << U"{:X}"_fmt(255);
	Print << U"{:x}"_fmt(255);
	Print << U"{:o}"_fmt(255);
	Print << U"{:b}"_fmt(255);
	Print << U"{:#X}"_fmt(255);
	Print << U"{:#x}"_fmt(255);
	Print << U"{:#o}"_fmt(255);
	Print << U"{:#b}"_fmt(255);

	while (System::Update())
	{

	}
}
