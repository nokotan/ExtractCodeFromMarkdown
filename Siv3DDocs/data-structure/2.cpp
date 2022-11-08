# include <Siv3D.hpp>

void Main()
{
	String s;

	if (s.isEmpty())
	{
		Print << U"s.isEmpty()";
	}

	if (not s)
	{
		Print << U"not s";
	}

	while (System::Update())
	{

	}
}
