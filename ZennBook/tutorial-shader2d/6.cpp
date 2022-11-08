# include <Siv3D.hpp>

void Main()
{
	// コンパイル済み HLSL シェーダを作って保存する（1 度だけ作成すれば OK）
	if (not Platform::Windows::CompileHLSLToFile(U"example/shader/hlsl/rgb_to_bgr.hlsl", U"rgb_to_bgr.ps", ShaderStage::Pixel, U"PS"))
	{
		throw Error{ U"Failed to save a shader file" };
	}

	const Texture windmill{ U"example/windmill.png" };

	// コンパイル済みの HLSL シェーダをロード
	const PixelShader ps = HLSL{ U"rgb_to_bgr.ps" };

	if (not ps)
	{
		throw Error{ U"Failed to load a shader file" };
	}

	while (System::Update())
	{
		{
			// R と B を入れ替えるピクセルシェーダを開始
			const ScopedCustomShader2D shader{ ps };
			windmill.draw(10, 10);
		}
	}
}
