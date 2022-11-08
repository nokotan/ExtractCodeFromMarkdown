# include <Siv3D.hpp>

void Main()
{
	const Font font20{ 20 };
	const Font font30{ 30, U"example/font/RocknRoll/RocknRollOne-Regular.ttf" };
	const Font font50{ 50 };

	const String text = U"Hello, Siv3D!";

	while (System::Update())
	{
		// ベースラインがそろわない
		font20(text).draw(20, 100);
		font30(text).draw(160, 100);
		font50(text).draw(380, 100);

		Rect{ 0, 400, 800, 10 }.draw(ColorF{ 0.3 });

		// (20, 400) がベースラインの開始位置になるようテキストを描画
		font20(text).drawBase(20, 400);

		// (160, 400) がベースラインの開始位置になるようテキストを描画
		font30(text).drawBase(160, 400);

		// (380, 400) がベースラインの開始位置になるようテキストを描画
		font50(text).drawBase(380, 400);
	}
}
