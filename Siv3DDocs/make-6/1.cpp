# include <Siv3D.hpp>

class Item
{
public:

	// クラスの初期化のためのメンバ関数（コンストラクタ）
	Item(const Emoji& emoji, const Vec2& pos, bool visible)
		: m_texture{ emoji }
		, m_circle{ pos, 80 }
		, m_visible{ visible } {}

	// 可視性を変更する
	void setVisibility(bool visible)
	{
		m_visible = visible;
	}

	// クリックされたかを返す
	bool clicked() const
	{
		if (not m_visible)
		{
			return false;
		}

		return m_circle.leftClicked();
	}

	// 描画する
	void draw() const
	{
		if (not m_visible)
		{
			return;
		}

		m_texture.drawAt(m_circle.center);

		if (m_circle.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);

			m_circle.draw(ColorF{ 1.0, 0.2 });
		}
	}

private:

	Texture m_texture;

	Circle m_circle;

	bool m_visible;
};

void Main()
{
	Scene::SetBackground(ColorF{ 0.9, 0.85, 0.8 });

	Item computer{ U"🖥️"_emoji, Vec2{ 200, 300 }, true };
	Item box{ U"🗃️"_emoji, Vec2{ 400, 300 }, true };
	Item door{ U"🚪"_emoji, Vec2{ 600, 300 }, true };

	while (System::Update())
	{
		computer.draw();
		box.draw();
		door.draw();

		if (computer.clicked())
		{
			Print << U"パソコンだ。電源は入らない。";
		}

		if (box.clicked())
		{
			Print << U"箱の中に何か入っている。部屋の鍵を見つけた！";
		}

		if (door.clicked())
		{
			Print << U"ドアには鍵がかかっている。出られない。";
		}
	}
}
