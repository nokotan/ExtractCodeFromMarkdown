# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		{
			// レンダーステートを変更（元の状態も保存）
			const ScopedRenderStates2D rasterizer{ RasterizerState::WireframeCullNone };

			Circle{ 200, 300, 150 }.draw();

		} // ここで rasterizer のデストラクタが呼び出され、レンダーステートを元の状態に戻す

		Circle{ 600, 300, 150 }.draw();
	}
}
