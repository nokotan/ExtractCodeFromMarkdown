# include <Siv3D.hpp>

void Main()
{
    Print << U"{}/{}"_fmt(-123, 123);
    Print << U"{:+}/{:+}"_fmt(-123, 123);
    Print << U"{: }/{: }"_fmt(-123, 123);
    Print << U"{}/{}"_fmt(0.5, -0.5);
    Print << U"{:+}/{:+}"_fmt(0.5, -0.5);
    Print << U"{: }/{: }"_fmt(0.5, -0.5);

    while (System::Update())
    {

    }
}
