# include <Siv3D.hpp>

struct GameData
{
	int32 score = 0;
};

using App = SceneManager<String, GameData>;

// タイトルシーン
class Title : public App::Scene
{
public:

	Title(const InitData& init)
		: IScene{ init }
	{

	}

	void update() override
	{
		if (MouseL.down())
		{
			// 0.3 秒かけてゲームシーンに遷移
			changeScene(U"Game", 0.3s);
		}
	}

	void draw() const override
	{
		Scene::SetBackground(ColorF{ 0.3, 0.4, 0.5 });

		FontAsset(U"TitleFont")(U"My Game").drawAt(400, 100);

		FontAsset(U"ScoreFont")(U"Score: {}"_fmt(getData().score)).draw(520, 540);

		Circle{ Cursor::Pos(), 50 }.draw(Palette::Orange);
	}
};

// ゲームシーン
class Game : public App::Scene
{
public:

	Game(const InitData& init)
		: IScene{ init }
		, m_texture{ U"🐈"_emoji }
	{

	}

	void update() override
	{
		if (MouseL.down())
		{
			// 2 秒かけてタイトルシーンに遷移
			changeScene(U"Title", 2.0s);
		}

		getData().score += static_cast<int32>(Cursor::Delta().length() * 10);
	}

	void draw() const override
	{
		Scene::SetBackground(ColorF(0.2, 0.8, 0.6));

		m_texture.drawAt(Cursor::Pos());

		FontAsset(U"ScoreFont")(U"Score: {}"_fmt(getData().score)).draw(40, 40);
	}

private:

	Texture m_texture;
};

void Main()
{
	FontAsset::Register(U"TitleFont", 60, Typeface::Heavy);
	FontAsset::Register(U"ScoreFont", 30, Typeface::Bold);

	App manager;
	manager.add<Title>(U"Title");
	manager.add<Game>(U"Game");

	// フェードイン・フェードアウト時の画面の色
	manager.setFadeColor(ColorF{ 0.8, 0.9, 1.0 });

	while (System::Update())
	{
		if (not manager.update())
		{
			break;
		}
	}
}
