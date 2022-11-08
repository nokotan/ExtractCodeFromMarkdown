# include <Siv3D.hpp>

void Main()
{
	const Texture texture{ U"aaa.png" };

	if (not texture)
	{
		// 例外を送出する
		throw Error{ U"Failed to load `aaa.png`" };
	}

	while (System::Update())
	{

	}
}
