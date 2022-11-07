# include <Siv3D.hpp>

using NodeID = int32;

struct Node
{
	NodeID id;
	Vec2 pos;

	Circle getCircle() const
	{
		return Circle{ pos, 40 };
	}

	void drawNode() const
	{
		getCircle()
			.drawShadow(Vec2{ 1, 1 }, 8, 1)
			.draw();
	}

	void drawNodeActive() const
	{
		getCircle()
			.drawShadow(Vec2{ 1, 1 }, 8, 1)
			.draw(ColorF{ 1.0, 0.9, 0.8 });
	}

	void drawLabel(const Font& font) const
	{
		font(id).drawAt(pos, ColorF{ 0.25 });
	}
};

struct Edge
{
	NodeID from;
	NodeID to;
};

void DrawEdge(const Node& from, const Node& to)
{
	Line{ from.pos, to.pos }
		.stretched(-40)
		.drawArrow(3, Vec2{ 10, 20 }, ColorF{ 0.25 });
}

void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	// MSDF 方式のフォントを生成
	const Font font{ FontMethod::MSDF, 40, Typeface::Bold };

	HashTable<NodeID, Node> nodes =
	{
		{ 0, Node{ 0, Vec2{ 200, 500 } }},
		{ 1, Node{ 1, Vec2{ 400, 100 } }},
		{ 2, Node{ 2, Vec2{ 600, 300 } }},
	};

	Array<Edge> edges =
	{
		Edge{ 0, 1 },
		Edge{ 1, 2 },
	};

	Optional<NodeID> activeNodeID;

	Camera2D camera{ Scene::Center(), 1.0 };

	while (System::Update())
	{
		ClearPrint();
		Print << activeNodeID;

		camera.update();
		{
			auto transformer = camera.createTransformer();

			if (MouseL.down())
			{
				activeNodeID = none;
			}

			for (const auto [nodeID, node] : nodes)
			{
				if (node.getCircle().mouseOver())
				{
					Cursor::RequestStyle(CursorStyle::Hand);
				}

				if (node.getCircle().leftClicked())
				{
					activeNodeID = nodeID;
				}
			}

			if (activeNodeID && MouseL.pressed())
			{
				nodes[activeNodeID.value()].pos += Cursor::DeltaF();
			}

			for (const auto& edge : edges)
			{
				DrawEdge(nodes[edge.from], nodes[edge.to]);
			}

			for (const auto [nodeID, node] : nodes)
			{
				if (nodeID == activeNodeID)
				{
					node.drawNodeActive();
				}
				else
				{
					node.drawNode();
				}

				node.drawLabel(font);
			}
		}

		camera.draw(Palette::Orange);
	}
}
