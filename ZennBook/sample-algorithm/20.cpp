# include <Siv3D.hpp>

class VisibilityMap
{
public:

	explicit VisibilityMap(const RectF& region)
		: m_region{ region }
		, m_maxDistance{ m_region.w + m_region.h }
	{
		add(m_region);
	}

	void add(const Triangle& t)
	{
		m_lines.emplace_back(t.p0, t.p1);
		m_lines.emplace_back(t.p1, t.p2);
		m_lines.emplace_back(t.p2, t.p0);
	}

	void add(const RectF& r)
	{
		m_lines.emplace_back(r.tl(), r.tr());
		m_lines.emplace_back(r.tr(), r.br());
		m_lines.emplace_back(r.br(), r.bl());
		m_lines.emplace_back(r.bl(), r.tl());
	}

	void add(const Quad& q)
	{
		m_lines.emplace_back(q.p0, q.p1);
		m_lines.emplace_back(q.p1, q.p2);
		m_lines.emplace_back(q.p2, q.p3);
		m_lines.emplace_back(q.p3, q.p0);
	}

	void add(const Circle& c, int32 quality = 8)
	{
		const double da = (2_pi / Max(quality, 6));

		for (auto i : step(quality))
		{
			m_lines.emplace_back(c.getPointByAngle(da * i), c.getPointByAngle(da * (i + 1)));
		}
	}

	void add(const Polygon& p)
	{
		const auto& outer = p.outer();

		for (auto i : step(outer.size()))
		{
			m_lines.emplace_back(outer[i], outer[(i + 1) % outer.size()]);
		}
	}

	template <class Shape>
	void add(const Array<Shape>& shapes)
	{
		for (const auto& shape : shapes)
		{
			add(shape);
		}
	}

	const RectF& getRegion() const
	{
		return m_region;
	}

	Array<Triangle> calculateVisibilityTriangles(const Vec2& eyePos) const
	{
		const auto points = calculateCollidePoints(eyePos);

		Array<Triangle> triangles(points.size());

		for (auto i : step(triangles.size()))
		{
			triangles[i].set(eyePos, points[i].second, points[(i + 1) % points.size()].first);
		}

		return triangles;
	}

private:

	static constexpr double m_epsilon = 1e-10;

	RectF m_region;

	double m_maxDistance = 0.0;

	Array<Line> m_lines;

	const Array<std::pair<Vec2, Vec2>> calculateCollidePoints(const Vec2& eyePos) const
	{
		if (not m_region.stretched(-1).contains(eyePos))
		{
			return{};
		}

		Array<double> angles{ Arg::reserve = m_lines.size() };
		{
			for (const auto& line : m_lines)
			{
				const Vec2 v = (line.begin - eyePos);
				angles.push_back(Math::Atan2(v.y, v.x));
			}
			angles.sort();
		}

		Array<std::pair<Vec2, Vec2>> points{ Arg::reserve = angles.size() };

		for (auto angle : angles)
		{
			const double left = (angle - m_epsilon);
			const double right = (angle + m_epsilon);
			const Line leftRay{ eyePos, Arg::direction = (Vec2::Right().rotated(left) * m_maxDistance) };
			const Line rightRay{ eyePos, Arg::direction = (Vec2::Right().rotated(right) * m_maxDistance) };

			Vec2 leftCollidePoint = leftRay.end;
			Vec2 rightCollidePoint = rightRay.end;

			for (const auto& line : m_lines)
			{
				if (const auto p = leftRay.intersectsAt(line))
				{
					if (p->distanceFromSq(eyePos) < leftCollidePoint.distanceFromSq(eyePos))
					{
						leftCollidePoint = *p;
					}
				}

				if (const auto p = rightRay.intersectsAt(line))
				{
					if (p->distanceFromSq(eyePos) < rightCollidePoint.distanceFromSq(eyePos))
					{
						rightCollidePoint = *p;
					}
				}
			}

			points.emplace_back(leftCollidePoint, rightCollidePoint);
		}

		return points;
	}
};

void Main()
{
	Window::Resize(1280, 720);

	constexpr ColorF objectColor = Palette::Deepskyblue;
	const Array<Triangle> triangles{ Triangle{ 120, 120, 300, 120, 120, 500 } };
	const Array<RectF> rects{ Rect{ 600, 40, 40, 260 }, Rect{ 440, 300, 440, 40 }, Rect{ 1040, 300, 200, 40 }, Rect{ 480, 480, 240, 100 } };
	const Array<Circle> circles{ Circle{ 1000, 500, 80 },  Circle{ 460, 180, 30 }, Circle{ 240, 480, 30 }, Circle{ 300, 560, 30 } };
	const Array<Polygon> polygons{ Shape2D::Star(60, Vec2{ 940, 180 }) };

	VisibilityMap map(Rect{ 40, 40, 1200, 640 });
	{
		map.add(triangles);
		map.add(rects);
		map.add(circles);
		map.add(polygons);
	}

	while (System::Update())
	{
		Cursor::RequestStyle(CursorStyle::Hidden);

		for (const auto& triangle : triangles)
		{
			triangle.draw(objectColor);
		}

		for (const auto& rect : rects)
		{
			rect.draw(objectColor);
		}

		for (const auto& circle : circles)
		{
			circle.draw(objectColor);
		}

		for (const auto& polygon : polygons)
		{
			polygon.draw(objectColor);
		}

		map.getRegion().drawFrame(0, 8, objectColor);

		const Vec2 eyePos = Cursor::Pos();

		const auto vTriangles = map.calculateVisibilityTriangles(eyePos);

		for (const auto& vTriangle : vTriangles)
		{
			vTriangle.draw(ColorF{ 1.0, 0.5 });
		}

		Circle{ eyePos, 20 }.draw(Palette::Orange).drawFrame(1, 2);
	}
}
