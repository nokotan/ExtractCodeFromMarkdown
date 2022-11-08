# include <Siv3D.hpp>

void Main()
{
	const Texture cat{ U"🐈"_emoji };

	const Texture dog{ U"🐕"_emoji };

	while (System::Update())
	{
		// 300px に拡大して描画
		cat.resized(300).drawAt(200, 300);

		// 200px に拡大して描画
		cat.resized(200).drawAt(400, 300);

		// 20px に縮小して描画
		dog.resized(20).drawAt(600, 300);
	}
}
