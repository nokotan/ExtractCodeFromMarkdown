# include <Siv3D.hpp>

struct Homography
{
	Float4 m1;
	Float4 m2;
	Float4 m3;
};

// チェッカーパターンの Image を作る
Image MakeCheckerPattern()
{
	Image image{ 1280, 720 , Palette::White };
	for (auto p : step(image.size() / Size{ 40, 40 }))
	{
		if (IsEven(p.x + p.y))
		{
			Rect{ p * 40, 40 }.overwrite(image, Color{ 40 });
		}
	}
	return image;
}

void Main()
{
	Window::Resize(1280, 720);
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	const Texture texture{ U"example/bay.jpg", TextureDesc::Mipped };
	const Texture checker{ MakeCheckerPattern(), TextureDesc::Mipped };

	constexpr double circleR = 12.0;
	const VertexShader vs = HLSL{ U"example/shader/hlsl/homography.hlsl", U"VS" }
		| GLSL{ U"example/shader/glsl/homography.vert", {{ U"VSConstants2D", 0 }, { U"VSHomography", 1} } };
	const PixelShader ps = HLSL{ U"example/shader/hlsl/homography.hlsl", U"PS" }
		| GLSL{ U"example/shader/glsl/homography.frag", {{ U"PSConstants2D", 0 }, { U"PSHomography", 1} } };

	if ((not vs) || (not ps))
	{
		throw Error{ U"Failed to load shader files" };
	}

	ConstantBuffer<Homography> vsHomography;
	ConstantBuffer<Homography> psHomography;

	Quad quad{ Vec2{100, 300}, Vec2{500, 300}, Vec2{500, 600}, Vec2{100, 600} };
	Optional<size_t> grabbedIndex;

	bool homography = true;

	while (System::Update())
	{
		SimpleGUI::CheckBox(homography, U"Homography", Vec2{ 40, 40 });

		if (homography)
		{
			const ScopedCustomShader2D shader{ vs, ps };
			const ScopedRenderStates2D sampler{ SamplerState::ClampAniso };

			{
				const Mat3x3 mat = Mat3x3::Homography(quad.movedBy(580, 0));
				vsHomography = { Float4{ mat._11_12_13, 0 }, Float4{ mat._21_22_23, 0 }, Float4{ mat._31_32_33, 0 } };
				Graphics2D::SetVSConstantBuffer(1, vsHomography);

				const Mat3x3 inv = mat.inverse();
				psHomography = { Float4{ inv._11_12_13, 0 }, Float4{ inv._21_22_23, 0 }, Float4{ inv._31_32_33, 0 } };
				Graphics2D::SetPSConstantBuffer(1, psHomography);

				// 1x1 の Rect に貼り付けて描くと、適切にホモグラフィ変換される
				Rect{ 1 }(checker).draw();
			}

			{
				const Mat3x3 mat = Mat3x3::Homography(quad);
				vsHomography = { Float4{ mat._11_12_13, 0 }, Float4{ mat._21_22_23, 0 }, Float4{ mat._31_32_33, 0 } };
				Graphics2D::SetVSConstantBuffer(1, vsHomography);

				const Mat3x3 inv = mat.inverse();
				psHomography = { Float4{ inv._11_12_13, 0 }, Float4{ inv._21_22_23, 0 }, Float4{ inv._31_32_33, 0 } };
				Graphics2D::SetPSConstantBuffer(1, psHomography);

				// 1x1 の Rect に貼り付けて描くと、適切にホモグラフィ変換される
				Rect{ 1 }(texture).draw();
			}
		}
		else
		{
			quad.movedBy(580, 0)(checker).draw();
			quad(texture).draw();
		}

		if (grabbedIndex)
		{
			if (not MouseL.pressed())
			{
				grabbedIndex.reset();
			}
			else
			{
				quad.p(*grabbedIndex).moveBy(Cursor::DeltaF());
			}
		}
		else
		{
			for (auto i : step(4))
			{
				const Circle circle = quad.p(i).asCircle(circleR);

				if (circle.mouseOver())
				{
					Cursor::RequestStyle(CursorStyle::Hand);
				}

				if (circle.leftClicked())
				{
					grabbedIndex = i;
					break;
				}
			}
		}

		for (auto i : step(4))
		{
			quad.p(i).asCircle(circleR).draw(ColorF{ 1.0, 0.3, 0.3, 0.5 });
		}
	}
}
