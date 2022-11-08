# include <Siv3D.hpp>

void Main()
{
	String s = U"Siv3D";

	s.pop_front();

	Print << s;

	s.pop_back();

	Print << s;

	while (System::Update())
	{

	}
}
