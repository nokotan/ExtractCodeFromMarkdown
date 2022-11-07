# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);

	constexpr Size size{ 1280, 720 };
	constexpr Rect rect{ size };
	Subdivision2D subdiv{ rect };

	for (const PoissonDisk2D pd{ size, 40 }; 
		const auto& point : pd.getPoints())
	{
		if (rect.contains(point))
		{
			subdiv.addPoint(point);
		}
	}

	const Array<Polygon> facetPolygons = subdiv
		.calculateVoronoiFacets()
		.map([rect](const VoronoiFacet& f)
	{
		return Geometry2D::And(Polygon{ f.points }, rect).front();
	});

	while (System::Update())
	{
		for (auto [i, facetPolygon] : Indexed(facetPolygons))
		{
			facetPolygon
				.draw(HSV{ i * 25.0, 0.65, 0.8 })
				.drawFrame(2, ColorF{ 0.25 });
		}
	}
}
