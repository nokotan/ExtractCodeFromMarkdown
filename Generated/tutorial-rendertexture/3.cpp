# include <Siv3D.hpp>

void Main()
{
	const Texture texture{ U"example/windmill.png" };

	// 縦、横が 3 分の 1 サイズのレンダーテクスチャ
	const RenderTexture renderTexture{ texture.size() / 3 };

	// ダウンサンプリング
	Shader::Downsample(texture, renderTexture);

	while (System::Update())
	{
		renderTexture.draw();
	}
}
