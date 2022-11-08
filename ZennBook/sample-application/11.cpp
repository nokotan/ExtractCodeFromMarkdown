# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	// 画像
	const Image image{ U"example/windmill.png" };

	// 表示用の動的テクスチャ
	DynamicTexture texture{ image };

	// JPEG のバイナリデータ
	const Blob originalBlob = image.encodeJPEG();

	// 改変するデータの個数
	const size_t noiseCount = (image.num_pixels() / 4000);

	while (System::Update())
	{
		if (SimpleGUI::Button(U"Glitch", Vec2{ 20, 20 }))
		{
			// Array を作成
			Blob modifiedBlob = originalBlob;

			for (size_t i = 0; i < noiseCount; ++i)
			{
				// ランダムな位置の 1 バイトについて、ランダムな値に書き換え
				// ヘッダ部分（先頭）は改変しない
				const size_t pos = Random<size_t>(630, modifiedBlob.size() - 1);
				modifiedBlob[pos] = Byte{ RandomUint8() };
			}

			// JPEG データとして読み込んで画像を作成、動的テクスチャに転送
			texture.fill(Image{ MemoryReader{ modifiedBlob }, ImageFormat::JPEG });
		}

		texture.drawAt(Scene::Center());
	}
}
