#include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	const Texture tree{ U"🌲"_emoji };

	while (System::Update())
	{
		// UV 座標が 0.0～1.0 の範囲を超えたとき、くり返しマッピング
		const ScopedRenderStates2D sampler{ SamplerState::RepeatLinear };

		// シーンのサイズぴったりにマッピングして描画
		tree.mapped(Scene::Size()).draw();
	}
}
