# include <Siv3D.hpp>

void Main()
{
	if (System::EnumerateMicrophones().isEmpty())
	{
		throw Error{ U"No microphone is connected" };
	}

	// 音声バッファ 5 秒、バッファ終端まで到達したら最初からループ、即座に録音開始
	// デフォルトの音声入力デバイス（マイク）、推奨サンプリングレートを使用
	const Microphone mic{ 5s, Loop::Yes, StartImmediately::Yes };

	if (not mic.isRecording())
	{
		throw Error{ U"Failed to start recording" };
	}

	LineString points(1600, Vec2{ 0, 300 });

	while (System::Update())
	{
		// 音声波形（サンプルの配列）にアクセス
		const Wave& wave = mic.getBuffer();

		// 現在のバッファ位置をもとに、直近の 1600 サンプルの波形を取得
		const size_t writePos = mic.posSample();
		{
			constexpr size_t samples_show = 1600;
			const size_t headLength = Min(writePos, samples_show);
			const size_t tailLength = (samples_show - headLength);
			size_t pos = 0;

			for (size_t i = 0; i < tailLength; ++i)
			{
				const float a = wave[wave.size() - tailLength + i].left;
				points[pos].set(pos * 0.5, 300 + a * 280);
				++pos;
			}

			for (size_t i = 0; i < headLength; ++i)
			{
				const float a = wave[writePos - headLength + i].left;
				points[pos].set(pos * 0.5, 300 + a * 280);
				++pos;
			}
		}

		// 音の波形の平均振幅 [0.0, 1.0]
		const double mean = mic.mean();

		// 音の波形の振幅の二乗平均平方根 [0.0, 1.0]
		const double rootMeanSquare = mic.rootMeanSquare();

		// 音の波形のピーク [0.0, 1.0]
		const double peak = mic.peak();

		// 波形の描画
		points.draw(2);

		Line{ 0, (300 - mean * 280), Arg::direction(800, 0) }.draw(2, HSV{ 200 });
		Line{ 0, (300 - rootMeanSquare * 280), Arg::direction(800, 0) }.draw(2, HSV{ 120 });
		Line{ 0, (300 - peak * 280), Arg::direction(800, 0) }.draw(2, HSV{ 40 });
	}
}
