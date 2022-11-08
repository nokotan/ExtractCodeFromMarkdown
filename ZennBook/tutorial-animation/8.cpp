# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(Palette::White);

	// ストップウォッチ（作成と同時に計測開始）
	Stopwatch stopwatch{ StartImmediately::Yes };

	while (System::Update())
	{
		// もし左クリックされたら
		if (MouseL.down())
		{
			// ストップウォッチをリセットして再び 0 から計測
			stopwatch.restart();
		}

		// ストップウォッチの経過時間（秒）を double 型で取得 
		const double t = stopwatch.sF();

		Circle{ Scene::Center(), (t * 50) }.draw(ColorF{ 0.25 });
	}
}
