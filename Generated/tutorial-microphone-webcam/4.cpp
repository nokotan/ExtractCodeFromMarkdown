# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);

	// デバイスインデックス 0 の Web カメラ、1280x720 かそれに近いサイズをリクエスト、即座に撮影開始
	Webcam webcam{ 0, Size{ 1280, 720 }, StartImmediately::Yes };

	DynamicTexture texture;

	while (System::Update())
	{
		// macOS では、ユーザがカメラ使用の権限を許可しないと Webcam の作成に失敗するため、再試行の手段を用意する
	# if SIV3D_PLATFORM(MACOS)
		if (not webcam)
		{
			if (SimpleGUI::Button(U"Retry", Vec2{ 20, 20 }))
			{
				webcam = Webcam{ 0, Size{ 1280, 720 }, StartImmediately::Yes };
			}
		}
	# endif

		// 新しい画像が撮影された
		if (webcam.hasNewFrame())
		{
			// DynamicTexture 画像に転送
			webcam.getFrame(texture);
		}

		if (texture)
		{
			texture.draw();
		}
	}
}
