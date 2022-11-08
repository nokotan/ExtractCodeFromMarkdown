# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		// ウィンドウタイトルに直近のフレームレートを表示
		Window::SetTitle(Profiler::FPS());
	}
}
