# include <Siv3D.hpp>

using NodeID = int32;

struct Node
{
	NodeID id;
	Vec2 pos;

	void drawNode() const
	{
		Circle{ pos, 40 }.draw();
	}

	// ラベル (id) の描画用メンバ関数
	void drawLabel(const Font& font) const
	{
		// font を使って id を描画
		font(id).drawAt(pos, ColorF{ 0.25 });
	}
};

void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	// ラベル描画用のフォント
	const Font font{ 40, Typeface::Bold };

	Node node{ 0, Vec2{ 400, 300 } };

	while (System::Update())
	{
		node.drawNode();

		// ラベルを描画
		node.drawLabel(font);
	}
}
