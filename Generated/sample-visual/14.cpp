# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });
	
	const VertexShader vs
		= HLSL{ U"example/shader/hlsl/soft_shape.hlsl" }
		| GLSL{ U"example/shader/glsl/soft_shape.vert", { { U"VSConstants2D", 0 }, { U"SoftShape", 1 } }};

	if (!vs)
	{
		throw Error{ U"Failed to load a shader file" };
	}

	ConstantBuffer<float> cb;

	while (System::Update())
	{
		cb = static_cast<float>(Scene::Time());
		Graphics2D::SetVSConstantBuffer(1, cb);
		
		{
			const ScopedCustomShader2D shader{ vs };

			// 頂点情報が未完成の三角形を 360 個描画
			// 頂点情報は頂点シェーダで生成
			Graphics2D::DrawTriangles(360);
		}
	}
}
