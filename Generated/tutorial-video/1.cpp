# include <Siv3D.hpp>

void Main()
{
	// GIF アニメーション画像を開く
	const AnimatedGIFReader gif{ U"example/gif/test.gif" };

	// 各フレームの画像と、次のフレームへのディレイ（ミリ秒）をロード
	Array<Image> images;
	Array<int32> delays;
	gif.read(images, delays);

	// フレーム数
	Print << images.size() << U" frames";

	// 各フレームのディレイ（ミリ秒）一覧
	Print << U"delays: " << delays;

	// 各フレームの Image から Texure を作成
	Array<Texture> textures;
	for (const auto& image : images)
	{
		textures << Texture{ image };
	}

	// 画像データはもう使わないので、消去してメモリ消費を減らす
	images.clear();

	while (System::Update())
	{
		// アニメーションの経過時間
		const double t = Scene::Time();

		// 経過時間と各フレームのディレイに基づいて、何番目のフレームを描けばよいかを計算
		const size_t frameIndex = AnimatedGIFReader::GetFrameIndex(t, delays);

		textures[frameIndex].draw(200, 200);
	}
}
