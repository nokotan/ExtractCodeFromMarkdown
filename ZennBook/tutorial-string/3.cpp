# include <Siv3D.hpp>

void Main()
{
	String s;

	s << U'S' << 'i';

	Print << s;

	s += U"v3D";

	Print << s;

	while (System::Update())
	{

	}
}
