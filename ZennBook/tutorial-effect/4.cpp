# include <Siv3D.hpp>

struct ScoreEffect : IEffect
{
	Vec2 m_start;

	int32 m_score;

	Font m_font;

	ScoreEffect(const Vec2& start, int32 score, const Font& font)
		: m_start{ start }
		, m_score{ score }
		, m_font{ font } {}

	bool update(double t) override
	{
		const HSV color{ (180 - m_score * 1.8), 1.0 - (t * 2.0) };

		m_font(m_score).drawAt(m_start.movedBy(0, t * -120), color);

		return (t < 0.5);
	}
};

void Main()
{
	const Font font{ 50, Typeface::Heavy };

	Effect effect;

	while (System::Update())
	{
		if (MouseL.down())
		{
			effect.add<ScoreEffect>(Cursor::Pos(), Random(0, 100), font);
		}

		effect.update();
	}
}
