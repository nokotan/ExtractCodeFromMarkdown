# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);

	// 非同期タスクを開始
	AsyncTask<Webcam> task{ []() { return Webcam{ 0, Size{ 1280, 720 }, StartImmediately::Yes }; } };

	Webcam webcam;
	DynamicTexture texture;

	while (System::Update())
	{
		// macOS では、ユーザがカメラ使用の権限を許可しないと Webcam の作成に失敗する。再試行の手段を用意する
	# if SIV3D_PLATFORM(MACOS)
		if ((not webcam) && (not task.valid()))
		{
			if (SimpleGUI::Button(U"Retry", Vec2{ 20, 20 }))
			{
				task = AsyncTask{ []() { return Webcam{ 0, Size{ 1280, 720 }, StartImmediately::Yes }; } };
			}
		}
	# endif
		
		if (task.isReady())
		{
			// 起動が完了した Webcam をタスクから取得
			webcam = task.get();

			if (webcam)
			{
				Print << webcam.getResolution();
			}
		}

		if (webcam.hasNewFrame())
		{
			webcam.getFrame(texture);
		}

		// Webcam 作成待機中は円を表示
		if (not webcam)
		{
			Circle{ Scene::Center(), 40 }
				.drawArc(Scene::Time() * 180_deg, 300_deg, 5, 5);
		}

		if (texture)
		{
			texture.draw();
		}
	}
}
