# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);
	Scene::SetBackground(ColorF{ 0.99 });
	const Rect rect{ 50, 50, Scene::Size() - Size{ 100, 100 } };

	Subdivision2D subdiv{ rect };

	// ドロネー三角形分割の三角形リスト
	Array<Triangle> triangles;

	// ボロノイ図の情報のリスト
	Array<VoronoiFacet> facets;

	// facets を長方形でクリップし Polygon に変換したリスト
	Array<Polygon> facetPolygons;

	while (System::Update())
	{
		const Vec2 pos = Cursor::Pos();

		// 長方形上をクリックしたら
		if (rect.leftClicked())
		{
			// 点を追加
			subdiv.addPoint(pos);

			// ドロネー三角形分割の計算
			subdiv.calculateTriangles(triangles);

			// ボロノイ図の計算
			subdiv.calculateVoronoiFacets(facets);

			// 長方形の範囲外をクリップ
			facetPolygons = facets.map([rect](const VoronoiFacet& f)
			{
				return Geometry2D::And(Polygon{ f.points }, rect).front();
			});
		}

		rect.draw(ColorF{ 0.75 });

		for (auto [i, facetPolygon] : Indexed(facetPolygons))
		{
			facetPolygon.draw(HSV{ (i * 25.0), 0.65, 0.8 }).drawFrame(3, ColorF{ 0.25 });
		}

		for (const auto& triangle : triangles)
		{
			triangle.drawFrame(2.5, ColorF{ 0.9 });
		}

		for (const auto& facet : facets)
		{
			Circle{ facet.center, 6 }.drawFrame(5).draw(ColorF{ 0.25 });
		}

		// 現在のマウスカーソルから最短距離にある点を探す
		if (const auto nearestVertexID = subdiv.findNearest(pos))
		{
			const Vec2 nearestVertex = subdiv.getVertex(nearestVertexID.value());
			Line{ pos, nearestVertex }.draw(LineStyle::RoundDot, 5, ColorF{ 0.6 });
			Circle{ nearestVertex, 16 }.drawFrame(3.5);
		}
	}
}
