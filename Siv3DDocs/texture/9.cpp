# include <Siv3D.hpp>

void Main()
{
	// ミップマップを作成しない設定
	const Texture unmipped{ U"example/windmill.png" };

	// ミップマップを作成する設定
	const Texture mipped{ U"example/windmill.png", TextureDesc::Mipped };

	while (System::Update())
	{
		const double scale = (0.02 + Periodic::Triangle0_1(10s) * 0.4);

		unmipped.scaled(scale).drawAt(300, 300);

		mipped.scaled(scale).drawAt(500, 300);
	}
}
