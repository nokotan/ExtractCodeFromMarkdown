# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);

	// 大きいと拡大描画時にきれいになるが、フォントの生成時間・メモリ消費が増える
	constexpr int32 fontSize = 70;

	// このサイズだけ、文字の周囲に輪郭や影のエフェクトを付加できる。フォントの生成時間・メモリ消費が増える
	constexpr int32 bufferThickness = 5;

	// ビットマップ方式では輪郭や影のエフェクトの利用は不可
	const Font fontBitmap{ FontMethod::Bitmap, fontSize, U"example/font/RocknRoll/RocknRollOne-Regular.ttf" };

	// SDF 方式
	const Font fontSDF{ FontMethod::SDF, fontSize, U"example/font/RocknRoll/RocknRollOne-Regular.ttf" };
	fontSDF.setBufferThickness(bufferThickness);

	// MSDF 方式
	const Font fontMSDF{ FontMethod::MSDF, fontSize, U"example/font/RocknRoll/RocknRollOne-Regular.ttf" };
	fontMSDF.setBufferThickness(bufferThickness);

	bool outline = false;
	bool shadow = false;
	double inner = 0.1, outer = 0.1;
	Vec2 shadowOffset{ 2.0, 2.0 };
	ColorF textColor{ 1.0 };
	ColorF outlineColor{ 0.0 };
	ColorF shadowColor{ 0.0, 0.5 };
	HSV background = ColorF{ 0.8 };

	Camera2D camera{ Scene::Center(), 1.0 };

	while (System::Update())
	{
		Scene::SetBackground(background);

		TextStyle textStyle;
		{
			if (outline && shadow)
			{
				textStyle = TextStyle::OutlineShadow(inner, outer, outlineColor, shadowOffset, shadowColor);
			}
			else if (outline)
			{
				textStyle = TextStyle::Outline(inner, outer, outlineColor);
			}
			else if (shadow)
			{
				textStyle = TextStyle::Shadow(shadowOffset, shadowColor);
			}
		}

		camera.update();
		{
			auto t = camera.createTransformer();
			fontBitmap(U"Siv3D, 渋三次元 (Bitmap)").draw(Vec2{ 100, 250 }, textColor);
			fontSDF(U"Siv3D, 渋三次元 (SDF)").draw(textStyle, Vec2{ 100, 330 }, textColor);
			fontMSDF(U"Siv3D, 渋三次元 (MSDF)").draw(textStyle, Vec2{ 100, 410 }, textColor);
		}

		SimpleGUI::CheckBox(outline, U"Outline", Vec2{ 20, 20 }, 130);
		SimpleGUI::Slider(U"Inner: {:.2f}"_fmt(inner), inner, -0.5, 0.5, Vec2{ 160, 20 }, 120, 120, outline);
		SimpleGUI::Slider(U"Outer: {:.2f}"_fmt(outer), outer, -0.5, 0.5, Vec2{ 160, 60 }, 120, 120, outline);

		SimpleGUI::CheckBox(shadow, U"Shadow", Vec2{ 20, 100 }, 130);
		SimpleGUI::Slider(U"offsetX: {:.1f}"_fmt(shadowOffset.x), shadowOffset.x, -5.0, 5.0, Vec2{ 160, 100 }, 120, 120, shadow);
		SimpleGUI::Slider(U"offsetY: {:.1f}"_fmt(shadowOffset.y), shadowOffset.y, -5.0, 5.0, Vec2{ 160, 140 }, 120, 120, shadow);

		SimpleGUI::Headline(U"Text", Vec2{ 420, 20 });
		SimpleGUI::Slider(U"R", textColor.r, Vec2{ 420, 60 }, 20, 80);
		SimpleGUI::Slider(U"G", textColor.g, Vec2{ 420, 100 }, 20, 80);
		SimpleGUI::Slider(U"B", textColor.b, Vec2{ 420, 140 }, 20, 80);
		SimpleGUI::Slider(U"A", textColor.a, Vec2{ 420, 180 }, 20, 80);

		SimpleGUI::Headline(U"Outline", Vec2{ 540, 20 });
		SimpleGUI::Slider(U"R", outlineColor.r, Vec2{ 540, 60 }, 20, 80, outline);
		SimpleGUI::Slider(U"G", outlineColor.g, Vec2{ 540, 100 }, 20, 80, outline);
		SimpleGUI::Slider(U"B", outlineColor.b, Vec2{ 540, 140 }, 20, 80, outline);
		SimpleGUI::Slider(U"A", outlineColor.a, Vec2{ 540, 180 }, 20, 80, outline);

		SimpleGUI::Headline(U"Shadow", Vec2{ 660, 20 });
		SimpleGUI::Slider(U"R", shadowColor.r, Vec2{ 660, 60 }, 20, 80, shadow);
		SimpleGUI::Slider(U"G", shadowColor.g, Vec2{ 660, 100 }, 20, 80, shadow);
		SimpleGUI::Slider(U"B", shadowColor.b, Vec2{ 660, 140 }, 20, 80, shadow);
		SimpleGUI::Slider(U"A", shadowColor.a, Vec2{ 660, 180 }, 20, 80, shadow);

		SimpleGUI::ColorPicker(background, Vec2{ 780, 20 });
	}
}
