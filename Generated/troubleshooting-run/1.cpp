# include <Siv3D.hpp>

// (Windows のみ) WARP ドライバによる Direct3D レンダリングを使用
SIV3D_SET(EngineOption::D3D11Driver::WARP);

void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	while (System::Update())
	{
		Circle{ Scene::Center(), 100 }.draw();
	}
}
