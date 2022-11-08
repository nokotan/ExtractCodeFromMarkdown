# include <Siv3D.hpp>

// 2 つの画像の距離を計算する関数
double Diff(const Image& a, const Image& b)
{
	const Color* pA = a.data();
	const Color* pB = b.data();
	const Color* const pAEnd = (pA + a.num_pixels());
	double d = 0.0;

	// すべてのピクセルに対して
	while (pA != pAEnd)
	{
		d += AbsDiff(pA->r, pB->r) + AbsDiff(pA->g, pB->g) + AbsDiff(pA->b, pB->b);
		++pA;
		++pB;
	}

	return d;
}

void Main()
{
	// 目標とする画像をファイルダイアログで選択、シーンのサイズにフィットするようリサイズ
	const Image target = Dialog::OpenImage().fit(Scene::Size());

	// 現在の画像
	Image image{ target.size(), Palette::White };

	// 直前の画像
	Image old = image;

	// 現在の画像を表示するための動的テクスチャ
	DynamicTexture texture{ image };

	// 目標との距離
	double d1 = Diff(target, image);

	while (System::Update())
	{
		for (int32 i = 0; i < 100; ++i)
		{
			// ランダムな座標
			const Point pos = RandomPoint(Rect{ image.size() });

			// ランダムな色 (rgb, a)
			const ColorF color{ Random(), Random() };

			// ランダムな半径
			const int32 size = Random(1, 10);

			// 円を現在の画像に書き込む
			Circle{ pos, size }.paint(image, color);

			// 目標との距離を計算
			const double d2 = Diff(target, image);

			if (d2 < d1) // 目標に近づいていたら採用
			{
				d1 = d2;
				old = image;
			}
			else // 近づいていなかったら元に戻す
			{
				image = old;
			}
		}

		// 動的テクスチャを更新
		texture.fill(image);

		// テクスチャを画面の中心に描画
		texture.drawAt(Scene::Center());

		// 保存ボタン
		if (SimpleGUI::Button(U"Save", Vec2{ 660, 550 }))
		{
			// 現在の画像をファイルダイアログ経由で保存
			image.saveWithDialog();
		}
	}
}
