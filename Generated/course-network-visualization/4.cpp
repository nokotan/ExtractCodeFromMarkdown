# include <Siv3D.hpp>

using NodeID = int32;

struct Node
{
	NodeID id;
	Vec2 pos;

	void drawNode() const
	{
		Circle{ pos, 40 }
			.drawShadow(Vec2{ 1, 1 }, 8, 1) // オフセット (1, 1), ぼかし半径 8px, 広がり 1px で影を描く
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

	Node node{ 0, Vec2{ 400, 300 } };

	while (System::Update())
	{
		node.drawNode();

		node.drawLabel(font);
	}
}
