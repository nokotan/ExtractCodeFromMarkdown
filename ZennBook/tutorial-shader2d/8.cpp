# include <Siv3D.hpp>

void Main()
{
	const Texture windmill{ U"example/windmill.png" };
	const PixelShader ps = HLSL{ U"example/shader/hlsl/grayscale.hlsl", U"PS" }
		| GLSL{ U"example/shader/glsl/grayscale.frag", {{U"PSConstants2D", 0}} };

	if (not ps)
	{
		throw Error{ U"Failed to load a shader file" };
	}

	while (System::Update())
	{
		{
			// グレースケール化するピクセルシェーダを開始
			const ScopedCustomShader2D shader{ ps };
			windmill.draw(10, 10);
		}
	}
}
