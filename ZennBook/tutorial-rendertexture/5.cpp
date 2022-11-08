# include <Siv3D.hpp>

void Main()
{
	// ウィンドウを 1280x720 にリサイズ
	Window::Resize(1280, 720);

	// bay.jpg は 2560x1440 なのでサイズを小さくしてロード
	const Texture texture{ Image{ U"example/bay.jpg" }.scale(1280, 720) };

	// ぼかしを適用する領域のサイズ
	constexpr Size blurAreaSize{ 480, 320 };

	// ガウスぼかしの中間で使うレンダーテクスチャを用意
	const RenderTexture gaussianA1{ blurAreaSize }, gaussianB1{ blurAreaSize };
	const RenderTexture gaussianA4{ blurAreaSize / 4 }, gaussianB4{ blurAreaSize / 4 };
	const RenderTexture gaussianA8{ blurAreaSize / 8 }, gaussianB8{ blurAreaSize / 8 };

	while (System::Update())
	{
		const Point cursorPos = Cursor::Pos();

		// 背景画像のうちぼかしを適用する領域
		const Rect blurArea{ cursorPos, blurAreaSize };

		// [オリジナル]->[ガウスぼかし]->[1/4サイズ]->[ガウスぼかし]->[1/8サイズ]->[ガウスぼかし]
		Shader::GaussianBlur(texture(blurArea), gaussianB1, gaussianA1);
		Shader::Downsample(gaussianA1, gaussianA4);
		Shader::GaussianBlur(gaussianA4, gaussianB4, gaussianA4);
		Shader::Downsample(gaussianA4, gaussianA8);
		Shader::GaussianBlur(gaussianA8, gaussianB8, gaussianA8);

		// 背景を描画
		texture.draw();

		// ガウスぼかし後のテクスチャを RoundRect に貼り付けて描画
		RoundRect{ cursorPos, blurAreaSize, 40 }(gaussianA8.resized(blurAreaSize)).draw();
	}
}
