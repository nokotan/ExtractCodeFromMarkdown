# include <Siv3D.hpp>

using NodeID = int32;

struct Node
{
	NodeID id;
	Vec2 pos;

	// 円の描画用のメンバ関数
	void drawNode() const
	{
		// 円を描画
		Circle{ pos, 40 }.draw();
	}
};

void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	Node node{ 0, Vec2{ 400, 300 } };

	while (System::Update())
	{
		// ノードを描画
		node.drawNode();
	}
}
