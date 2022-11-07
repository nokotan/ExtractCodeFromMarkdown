# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);

	const Image image1{ U"🐤"_emoji };
	const Image image2{ U"example/windmill.png" };

	const Texture texture1{ image1 };
	const Texture texture2{ image2 };

	// 画像をアフィン変換
	const Mat3x2 mat = Mat3x2::Rotate(50_deg, image1.size() / 2.0);
	const Texture texture1t{ image1.warpAffine(mat) };

	// 画像を射影変換
	const Quad q{ Vec2{ 0, 80 }, Vec2{ 400, 0 }, Vec2{ 400, 300 }, Vec2{ 0, 220 } };
	const Texture texture2t{ image2.warpPerspective(q) };

	while (System::Update())
	{
		texture1.draw(0, 0);
		texture2.draw(0, 200);

		texture1t.draw(600, 0).drawFrame(1, 0);
		texture2t.draw(600, 200).drawFrame(1, 0);
	}
}
