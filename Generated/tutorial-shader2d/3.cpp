# include <Siv3D.hpp>

void Main()
{
	const VertexShader vs2D = HLSL{ U"example/shader/hlsl/default2d.hlsl", U"VS" }
		| GLSL{ U"example/shader/glsl/default2d.vert", {{U"VSConstants2D", 0}} };

	const PixelShader ps2DShape = HLSL{ U"example/shader/hlsl/default2d.hlsl", U"PS_Shape" }
		| GLSL{ U"example/shader/glsl/default2d_shape.frag", {{U"PSConstants2D", 0}} };

	const PixelShader ps2DTexture = HLSL{ U"example/shader/hlsl/default2d.hlsl", U"PS_Texture" }
		| GLSL{ U"example/shader/glsl/default2d_texture.frag", {{U"PSConstants2D", 0}} };

	if ((not vs2D) || (not ps2DShape) || (not ps2DTexture))
	{
		throw Error{ U"Failed to load shader files" };
	}

	while (System::Update())
	{

	}
}
