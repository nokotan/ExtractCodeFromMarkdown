# include <Siv3D.hpp>

void Main()
{
	Print << IsASCII(U'A') << U' ' << IsASCII(U'あ');
	Print << IsUpper(U'A') << U' ' << IsUpper(U'a');
	Print << IsAlnum(U'4') << U' ' << IsAlnum(U'#');
	Print << IsSpace(U' ') << U' ' << IsSpace(U'-');
	Print << ToLower(U'A') << U' ' << ToLower(U'a');

	while (System::Update())
	{

	}
}
