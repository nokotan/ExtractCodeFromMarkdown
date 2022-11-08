# include <Siv3D.hpp>

void Main()
{
	if (System::EnumerateMicrophones().isEmpty())
	{
		throw Error{ U"No microphone is connected" };
	}

	// デフォルトの音声入力デバイス（マイク）、推奨サンプリングレート、5 秒間のバッファを使用
	const Microphone mic{ StartImmediately::Yes };

	if (not mic.isRecording())
	{
		throw Error{ U"Failed to start recording" };
	}

	FFTResult fft;

	while (System::Update())
	{
		// FFT の結果を取得
		mic.fft(fft);

		// 結果を可視化
		for (auto i : step(800))
		{
			const double size = Pow(fft.buffer[i], 0.6f) * 1200;
			RectF{ Arg::bottomLeft(i, 600), 1, size }.draw(HSV{ 240 - i });
		}

		// 周波数表示
		Rect{ Cursor::Pos().x, 0, 1, Scene::Height() }.draw();
		ClearPrint();
		Print << U"{:.2f} Hz"_fmt(Cursor::Pos().x * fft.resolution);
	}
}
