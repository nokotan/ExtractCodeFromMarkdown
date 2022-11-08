# include <Siv3D.hpp>

void Main()
{
	const Texture texture{ U"example/windmill.png" };

	Print << texture.size();

	Print << texture.width();

	Print << texture.height();

	while (System::Update())
	{
		Rect{ 0, 0, texture.size() }.draw();
	}
}
