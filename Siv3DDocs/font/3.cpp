# include <Siv3D.hpp>

void Main()
{
	const Font fontThin{ 36, Typeface::Thin };
	const Font fontLight{ 36, Typeface::Light };
	const Font fontRegular{ 36, Typeface::Regular };
	const Font fontMedium{ 36, Typeface::Medium };
	const Font fontBold{ 36, Typeface::Bold };
	const Font fontHeavy{ 36, Typeface::Heavy };
	const Font fontBlack{ 36, Typeface::Black };

	const Font fontJP{ 36, Typeface::CJK_Regular_JP };
	const Font fontKR{ 36, Typeface::CJK_Regular_KR };
	const Font fontSC{ 36, Typeface::CJK_Regular_SC };
	const Font fontTC{ 36, Typeface::CJK_Regular_TC };
	const Font fontHK{ 36, Typeface::CJK_Regular_HK };

	const Font fontMono{ 36, Typeface::MonochromeEmoji };

	// カラー絵文字フォントは、サイズの指定が無視される仕様
	const Font fontEmoji{ 36, Typeface::ColorEmoji };

	const String s0 = U"Hello, Siv3D!";
	const String s1 = U"こんにちは 你好 안녕하세요 骨曜喝愛遙扇";
	const String s2 = U"🐈🐕🚀";

	while (System::Update())
	{
		fontThin(s0).draw(20, 20);
		fontLight(s0).draw(20, 60);
		fontRegular(s0).draw(20, 100);
		fontMedium(s0).draw(20, 140);
		fontBold(s0).draw(20, 180);
		fontHeavy(s0).draw(20, 220);
		fontBlack(s0).draw(20, 260);

		fontJP(s1).draw(20, 300);
		fontKR(s1).draw(20, 340);
		fontSC(s1).draw(20, 380);
		fontTC(s1).draw(20, 420);
		fontHK(s1).draw(20, 460);

		fontMono(s2).draw(20, 500);
		fontEmoji(s2).draw(20, 540);
	}
}
