# include <Siv3D.hpp>

void Main()
{
	const Texture textureWindmill{ U"example/windmill.png", TextureDesc::Mipped };
	const Texture textureSiv3DKun{ U"example/siv3d-kun.png", TextureDesc::Mipped };

	const RoundRect roundRect{ 430, 50, 100, 100, 25 };
	const Circle circle{ 480, 240, 50 };
	const Polygon hexagon = Shape2D::Hexagon(60, Vec2{ 480, 380 });

	while (System::Update())
	{
		// テクスチャを長方形に貼り付けて描画
		Rect{ 50, 50, 350, 400 }(textureWindmill).draw();

		roundRect.draw(HSV{ 0, 0.5, 1.0 });
		// テクスチャの (90, 5) から幅 110 高さ 110 の領域を、roundRect に貼り付けて描画
		roundRect(textureSiv3DKun(90, 5, 110, 110)).draw();

		circle.draw(HSV{ 120, 0.5, 1.0 });
		// テクスチャの (85, 0) から幅 120 高さ 120 の領域を、circle に貼り付けて描画
		circle(textureSiv3DKun(85, 0, 120, 120)).draw();

		hexagon.draw(HSV{ 240, 0.5, 1.0 });
		// Polygon に対し、(515, 560) を画像の中心とするようにテクスチャを貼り付けて描画
		hexagon.toBuffer2D(Arg::center(515, 560), textureSiv3DKun.size())
			.draw(textureSiv3DKun);
	}
}
