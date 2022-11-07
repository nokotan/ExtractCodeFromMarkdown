# include <Siv3D.hpp>

// ノード ID を表す型エイリアス
using NodeID = int32;

// ノードクラス
struct Node
{
	NodeID id; // ID
	Vec2 pos; // 中心座標
};

void Main()
{
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	// ノード
	Node node{ 0, Vec2{ 400, 300 } };

	while (System::Update())
	{

	}
}
