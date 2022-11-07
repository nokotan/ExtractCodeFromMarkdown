# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);

	// 非同期タスクを開始
	AsyncTask<Webcam> task{ []() { return Webcam{ 0, Size{ 1280, 720 }, StartImmediately::Yes }; } };

	Webcam webcam;
	Image image;
	DynamicTexture texture;

	// 検出器。正面を向いた顔の学習データを使用して分類
	const CascadeClassifier faceDetector{ U"example/objdetect/haarcascade/frontal_face_alt2.xml" };

	// 検出された領域
	Array<Rect> rects;

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
			webcam.getFrame(image);

			// 画像から顔を検出。厳密さ: 3, 最小領域サイズ:　100x100
			rects = faceDetector.detectObjects(image, 3, Size{ 100, 100 });

			// 領域にモザイクエフェクトをかける
			for (const auto& rect : rects)
			{
				image(rect).mosaic(20);
			}

			texture.fill(image);
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

		for (const auto& rect : rects)
		{
			rect.drawFrame(4, Palette::Red);
		}
	}
}
