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

class ItemManager
{
public:

	// デフォルトコンストラクタ
	ItemManager() = default;

	// 新しい Item を追加するメンバ関数
	void add(const Vec2& center, const ColorF& color)
	{
		// 配列に Item を追加
		m_items.emplace_back(center, color);

		// エフェクトを追加
		m_effect.add([center](double t)
		{
			const double e = EaseOutExpo(t);
			Circle{ center, (Item::CircleR + e * 30) }
				.drawFrame(0, 4 * e, ColorF{ 1.0, (1 - e) });
			return t < 1.0;
		});
	}

	// すべての Item とエフェクトを描画するメンバ関数
	void draw() const
	{
		// エフェクトを更新・描画
		m_effect.update();

		// 配列内の Item を描画
		for (const auto& item : m_items)
		{
			item.draw();
		}
	}

private:

	// Item を格納する配列
	Array<Item> m_items;

	// エフェクト
	Effect m_effect;
};

void Main()
{
	ItemManager itemManager;

	while (System::Update())
	{
		// もしシーンが左クリックされたら
		if (Scene::Rect().leftClicked())
		{
			// 追加
			itemManager.add(Cursor::Pos(), RandomColorF());
		}

		// 描画
		itemManager.draw();
	}
}
