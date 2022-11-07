# include <Siv3D.hpp>

void Main()
{
	if (false)
	{
		throw Error{ U"A1" };
	}

	int32 a = 10;

	if (true)
	{
		throw Error{ U"A2" };
	}

	int32 b = 20;

	while (System::Update())
	{

	}
}
