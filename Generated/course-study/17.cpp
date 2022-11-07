# include <Siv3D.hpp>

void Main()
{
	// 背景色を ColorF{ 0.3, 0.6, 1.0 } に設定
	Scene::SetBackground(ColorF{ 0.3, 0.6, 1.0 });

	while (System::Update())
	{
		Circle{ Cursor::Pos(), 80 }.draw();
	}
}
