# include <Siv3D.hpp>

void Main()
{
	Texture texture;

	double scale = 1.0;

	// 検出器。正面を向いた顔の学習データを使用して分類
	const CascadeClassifier animeFaceDetector{ U"example/objdetect/haarcascade/face_anime.xml" };

	Array<Rect> detectedFaces;

	while (System::Update())
	{
		// ファイルがドロップされた
		if (DragDrop::HasNewFilePaths())
		{
			// ファイルを画像として読み込めた
			if (const Image image{ DragDrop::GetDroppedFilePaths().front().path })
			{
				// イラストの顔を検出
				detectedFaces = animeFaceDetector.detectObjects(image);

				// 画面のサイズに合うように画像を拡大縮小
				texture = Texture{ image.fitted(Scene::Size()) };

				// 画像の拡大縮小率
				scale = static_cast<double>(texture.width()) / image.width();
			}
		}

		if (texture)
		{
			texture.draw(0, 0);

			// 顔の領域の座標を表示に合わせる
			const Transformer2D transformer{ Mat3x2::Scale(scale) };

			for (const auto& detectedFace : detectedFaces)
			{
				detectedFace.drawFrame((4 / scale), ColorF{ 1.0, 0.0, 0.0, Periodic::Sine0_1(1.5s) });
			}
		}
	}
}
