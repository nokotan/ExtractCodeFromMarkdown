# include <Siv3D.hpp>

void Main()
{
	// 埋め込みリソースから読み込み
	const Texture texture{ Resource(U"example/windmill.png") };

	while (System::Update())
	{
		texture.draw();
	}
}
