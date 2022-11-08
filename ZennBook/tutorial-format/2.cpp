# include <Siv3D.hpp>

void Main()
{
	Print << U"{2}/{1}/{0}"_fmt(2021, 12, 31);

	Print << U"{0}/{1}/{2}"_fmt(2021, 12, 31);

	Print << U"C{0}{0}"_fmt(U'+');

	Print << U"{0} - {1} - {0}"_fmt(U"Tokyo", U"Osaka");

	while (System::Update())
	{

	}
}
