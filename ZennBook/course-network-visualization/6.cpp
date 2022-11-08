# include <Siv3D.hpp>

using NodeID = int32;

struct Node
{
	NodeID id;
	Vec2 pos;

	// ノードの円を返すメンバ関数
	Circle getCircle() const
	{
		return Circle{ pos, 40 };
	}

	void drawNode() const
	{
		getCircle() // getCircle() に置き換え
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

	while (System::Update())
	{
		// range-based for で各エントリにアクセス
		for (const auto [nodeID, node] : nodes)
		{
			// 円とマウスカーソルが重なっていたら
			if (node.getCircle().mouseOver())
			{
				// カーソルを手のアイコンに
				Cursor::RequestStyle(CursorStyle::Hand);
			}
		}

		for (const auto [nodeID, node] : nodes)
		{
			node.drawNode();

			node.drawLabel(font);
		}
	}
}
