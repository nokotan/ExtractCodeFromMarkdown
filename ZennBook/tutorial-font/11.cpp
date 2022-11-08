# include <Siv3D.hpp>

void Main()
{
	const Font font{ 50 };
	const String text = U"Hello, Siv3D!";
	constexpr Vec2 pos{ 20, 20 };

	// font を使って text を pos の位置に描画したときのテキストの領域を取得
	const RectF rect = font(text).region(pos);

	while (System::Update())
	{
		// 描画領域の長方形を事前に塗りつぶす
		rect.draw(Palette::Skyblue);

		// 長方形の上にテキストを描く
		font(text).draw(pos, ColorF{ 0.25 });

		// テキストの領域を
		font(text)
			.drawAt(Scene::Center())
			.stretched(40, 0)	// 横に広げて
			.shearedX(20)		// 平行四辺形にして
			.drawFrame(2);		// 枠を描く
	}
}
