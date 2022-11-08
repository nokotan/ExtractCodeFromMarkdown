# include <Siv3D.hpp>

using App = SceneManager<String>;

// タイトルシーン
class Title : public App::Scene
{
public:

	Title(const InitData& init)
		: IScene{ init }
	{
		Print << U"Title::Title()";
	}

	~Title()
	{
		Print << U"Title::~Title()";
	}

	void update() override
	{
		// 左クリックで
		if (MouseL.down())
		{
			// ゲームシーンに遷移
			changeScene(U"Game");
		}
	}

	void draw() const override
	{
		Scene::SetBackground(ColorF{ 0.3, 0.4, 0.5 });

		FontAsset(U"TitleFont")(U"My Game").drawAt(400, 100);

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
		Print << U"Game::Game()";
	}

	~Game()
	{
		Print << U"Game::~Game()";
	}

	void update() override
	{
		// 左クリックで
		if (MouseL.down())
		{
			// タイトルシーンに遷移
			changeScene(U"Title");
		}
	}

	void draw() const override
	{
		Scene::SetBackground(ColorF(0.2, 0.8, 0.6));

		m_texture.drawAt(Cursor::Pos());
	}

private:

	Texture m_texture;
};

void Main()
{
	FontAsset::Register(U"TitleFont", 60, Typeface::Heavy);

	// シーンマネージャーを作成
	App manager;

	// タイトルシーン（名前は "Title"）を登録
	manager.add<Title>(U"Title");

	// ゲームシーン（名前は "Game"）を登録
	manager.add<Game>(U"Game");

	while (System::Update())
	{
		if (not manager.update())
		{
			break;
		}
	}
}
