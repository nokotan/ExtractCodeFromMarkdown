# include <Siv3D.hpp>

void Main()
{
	// ウィンドウの枠を非表示にする
	Window::SetStyle(WindowStyle::Frameless);

	while (System::Update())
	{
		Circle{ Cursor::Pos(), 100 }.draw();
	}
}
