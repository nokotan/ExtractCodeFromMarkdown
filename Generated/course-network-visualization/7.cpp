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

	void drawLabel(const Font& font) const
	{
		font(id).drawAt(pos, ColorF{ 0.25 });
	}
};

void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	const Font font{ 40, Typeface::Bold };

	HashTable<NodeID, Node> nodes =
	{
		{ 0, Node{ 0, Vec2{ 200, 500 } }},
		{ 1, Node{ 1, Vec2{ 400, 100 } }},
		{ 2, Node{ 2, Vec2{ 600, 300 } }},
	};

	// 選択中のノードの ID を保持する変数。初期値は none
	Optional<NodeID> activeNodeID;

	while (System::Update())
	{
		// デバッグ用の表示
		ClearPrint();
		Print << activeNodeID;

		// 左クリックされたら activeNodeID を none にリセット
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

			// 円が左クリックされていたら
			if (node.getCircle().leftClicked())
			{
				// activeNodeID にそのノードの ID をセット
				activeNodeID = nodeID;
			}
		}

		for (const auto [nodeID, node] : nodes)
		{
			node.drawNode();

			node.drawLabel(font);
		}
	}
}
