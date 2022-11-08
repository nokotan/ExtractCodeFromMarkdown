# include <Siv3D.hpp>

struct Item
{
	// 円の半径 (定数）
	static constexpr double CircleR = 24.0;

	// 円の中心座標
	Vec2 center;

	// 円の色
	ColorF color;

	// デフォルトコンストラクタ
	Item() = default;

	// 座標、色を初期化するコンストラクタ
	Item(const Vec2& _center, const ColorF& _color)
		: center{ _center }
		, color{ _color } {}

	// 円を描画するメンバ関数
	void draw() const
	{
		Circle{ center, CircleR }.draw(color);
	}
};

void Main()
{
	// Item を格納する配列
	Array<Item> items;

	while (System::Update())
	{
		// もしシーンが左クリックされたら
		if (Scene::Rect().leftClicked())
		{
			// 配列に Item を追加
			items.emplace_back(Cursor::Pos(), RandomColorF());
		}

		// 配列内の Item を描画
		for (const auto& item : items)
		{
			item.draw();
		}
	}
}
