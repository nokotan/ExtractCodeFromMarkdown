# include <Siv3D.hpp>

void Main()
{
	const Font font{ 50 };

	while (System::Update())
	{
		font(U"Hello,\nSiv3D\n\n!!!").draw(20, 20);
	}
}
