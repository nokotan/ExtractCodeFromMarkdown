# include <Siv3D.hpp>

// パターン画像を作る
Image CreatePattern()
{
	Image image{ 16, 16, Palette::White };
	Circle{ 0, 4, 2 }.paint(image, Palette::Black);
	Circle{ 8, 4, 2 }.paint(image, Palette::Black);
	Circle{ 16, 4, 2 }.paint(image, Palette::Black);
	Circle{ 4, 12, 2 }.paint(image, Palette::Black);
	Circle{ 12, 12, 2 }.paint(image, Palette::Black);
	return image;
}

// 定数バッファ (PS_1)
struct PatternBrush
{
	// パターンの UV のスケール
	Float2 uvScale;
};

void Main()
{
	constexpr Size sceneSize{ 600, 600 };

	// パターン画像のテクスチャ
	const Texture patternTexture{ CreatePattern(), TextureDesc::Mipped };

	// パターンブラシ用のピクセルシェーダ
	const PixelShader ps = HLSL{ U"pattern_brush.hlsl", U"PS" }
		| GLSL{ U"pattern_brush.frag", {{ U"PSConstants2D", 0 }, { U"PatternBrush", 1 }} };

	if (not ps)
	{
		throw Error{ U"Failed to load a shader file" };
	}

	// 定数バッファ
	ConstantBuffer<PatternBrush> cb;
	cb->uvScale = (Float2{ sceneSize } / patternTexture.size());

	// ペンで書き込むレンダーテクスチャ
	MSRenderTexture renderTexture{ sceneSize, Palette::Black };

	// ペンの太さ
	constexpr double thickness = 20;

	while (System::Update())
	{
		if (MouseL.pressed())
		{
			{
				const ScopedRenderTarget2D target{ renderTexture };

				if (MouseL.down())
				{
					Circle{ Cursor::PosF(), thickness * 0.5 }.draw();
				}
				else if (MouseL.pressed() && (not Cursor::Delta().isZero()))
				{
					Line{ Cursor::PreviousPosF(), Cursor::PosF() }
						.draw(LineStyle::RoundCap, thickness);
				}
			}

			Graphics2D::Flush();
			renderTexture.resolve();
		}

		Rect{ sceneSize }.draw();
		{
			// パターン画像を PS テクスチャスロット 1 にセット 
			Graphics2D::SetPSTexture(1, patternTexture);
			Graphics2D::SetPSConstantBuffer(1, cb);

			// パターンをくり返しマッピングできるようにする
			{
				const ScopedRenderStates2D sampler{ {ShaderStage::Pixel, 1, SamplerState::RepeatLinear} };
				const ScopedCustomShader2D shader{ ps };
				renderTexture.draw();
			}
		}

		// パターン画像を右上に表示
		patternTexture.draw(620, 20);
	}
}
