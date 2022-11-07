# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		ClearPrint();
		Print << Cursor::Pos();
		Print << Cursor::PosF();

		Circle{ Cursor::Pos(), 50 }.draw(Palette::Skyblue);
	}
}
