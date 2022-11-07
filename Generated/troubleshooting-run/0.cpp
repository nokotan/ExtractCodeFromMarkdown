# include <Siv3D.hpp>

// (Windows のみ) Direct3D の代わりに OpenGL レンダリングエンジンを使用
SIV3D_SET(EngineOption::Renderer::OpenGL);

void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	while (System::Update())
	{
		Circle{ Scene::Center(), 100 }.draw();
	}
}
