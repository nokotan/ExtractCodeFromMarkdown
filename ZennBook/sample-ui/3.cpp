# include <Siv3D.hpp>

struct Button
{
	Rect rect;
	String label;
};

class PenEffect
{
public:

	PenEffect() = default;

	explicit PenEffect(const Size& size)
		: m_texture{ size, ColorF{ 1.0, 0.0 } }
	{
		initLines();
	}

	void reset()
	{
		initLines();
		m_texture.clear(ColorF{ 1.0, 0.0 });
		m_texture.resolve();
	}

	void update(double delta)
	{
		m_accumulatedLength = Min(m_accumulatedLength + (m_length * delta), m_length);

		if ((4.0 <= (m_accumulatedLength - m_paintedLength)))
		{
			BlendState bs = BlendState::Default2D;
			bs.srcAlpha = Blend::SrcAlpha;
			bs.dstAlpha = Blend::DestAlpha;
			bs.opAlpha = BlendOp::Max;
			const ScopedRenderStates2D blend(bs);
			const ScopedRenderTarget2D target{ m_texture };

			while (4.0 <= (m_accumulatedLength - m_paintedLength))
			{
				m_lines.calculatePointFromOrigin(m_paintedLength)
					.asCircle(6).draw(ColorF{ 1.0 });

				m_paintedLength += 4.0;
			}

			Graphics2D::Flush();
			m_texture.resolve();
		}
	}

	const Texture& getTexture() const
	{
		return m_texture;
	}

private:

	void initLines()
	{
		m_lines.clear();

		const Size size = m_texture.size();

		Point penPos{ 8, (size.y - Random(8, 24)) };

		for (;;)
		{
			m_lines << penPos;
			penPos.x += Random(18, 28);
			penPos.y = Random(6, 20);

			if ((size.x - 8) < penPos.x)
			{
				break;
			}

			m_lines << penPos;
			penPos.x -= Random(8, 16);
			penPos.y = size.y - Random(6, 20);
		}

		m_length = m_lines.calculateLength();
		m_accumulatedLength = 0.0;
		m_paintedLength = 0.0;
	}

	MSRenderTexture m_texture;

	LineString m_lines;

	double m_length = 0.0;

	double m_accumulatedLength = 0.0;

	double m_paintedLength = 0.0;
};

void Main()
{
	const ColorF backgroundColor{ 1.0, 0.98, 0.96 };
	Scene::SetBackground(backgroundColor);

	const Array<Button> buttons =
	{
		Button{ Rect{ Arg::center(400, 300), 300, 80 }, U"あそぶ" },
		Button{ Rect{ Arg::center(400, 400), 300, 80 }, U"スコア" },
		Button{ Rect{ Arg::center(400, 500), 300, 80 }, U"おわる" },
	};

	const Font font{ FontMethod::MSDF, 40, Typeface::Bold };

	Array<PenEffect> penEffects =
	{
		PenEffect{ Size{300, 90} },
		PenEffect{ Size{300, 90} },
		PenEffect{ Size{300, 90} }
	};

	Optional<size_t> selectedItem;
	Stopwatch stopwatch{ StartImmediately::Yes };

	while (System::Update())
	{
		if (SimpleGUI::Button(U"Restart", Vec2{ 20,20 }))
		{
			for (auto& penEffect : penEffects)
			{
				penEffect.reset();
			}

			stopwatch.restart();
		}

		for (auto [i, penEffect] : Indexed(penEffects))
		{
			if ((i * 250) < stopwatch.ms())
			{
				penEffects[i].update(Scene::DeltaTime() * 0.5);
			}
		}

		selectedItem.reset();
		
		for (auto [i, button] : Indexed(buttons))
		{
			if (button.rect.mouseOver())
			{
				selectedItem = i;
				Cursor::RequestStyle(CursorStyle::Hand);
			}

			const bool selected = (selectedItem == i);

			penEffects[i].getTexture().drawAt(button.rect.center(), HSV{ 30 + i * 60});

			font(button.label)
				.drawAt(TextStyle::OutlineShadow(0.3, HSV{ backgroundColor } - HSV{0.0, 0.0, 0.5}, Vec2{0, 0}, backgroundColor),
					(selected ? 48 : 40), button.rect.center(), ColorF{ 1.0, 0.0 });
		}
	}
}
