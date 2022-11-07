# include <Siv3D.hpp>

void Main()
{
	// ウィンドウを 1280x720 にリサイズ
	Window::Resize(1280, 720);

	// 背景色を設定
	Scene::SetBackground(ColorF{ 0.2, 0.6, 1.0 });

	// 登場する絵文字
	const Array<String> emojis = { U"🐘", U"🐧", U"🐐", U"🐤" };
	Array<MultiPolygon> polygons;
	Array<Texture> textures;
	for (const auto& emoji : emojis)
	{
		// 絵文字の画像から形状情報を作成
		polygons << Emoji::CreateImage(emoji).alphaToPolygonsCentered().simplified(2.0);

		// 絵文字の画像からテクスチャを作成
		textures << Texture{ Emoji{ emoji } };
	}

	// 2D 物理演算のシミュレーションステップ（秒）
	constexpr double stepSec = (1.0 / 200.0);

	// 2D 物理演算のシミュレーション蓄積時間（秒）
	double accumulatorSec = 0.0;

	// 2D 物理演算のワールド
	P2World world;

	// [_] 地面
	const P2Body ground = world.createLine(P2Static, Vec2{ 0, 0 }, Line{ -300, 0, 300, 0 });

	// 動物の物体
	Array<P2Body> bodies;

	// 物体の ID と絵文字のインデックスの対応テーブル
	HashTable<P2BodyID, size_t> table;

	// 絵文字のインデックス
	size_t index = Random(polygons.size() - 1);

	// 2D カメラ
	Camera2D camera{ Vec2{ 0, -200 } };

	while (System::Update())
	{
		for (accumulatorSec += Scene::DeltaTime(); stepSec <= accumulatorSec; accumulatorSec -= stepSec)
		{
			// 2D 物理演算のワールドを更新
			world.update(stepSec);
		}

		// 地面より下に落ちた物体は削除
		for (auto it = bodies.begin(); it != bodies.end();)
		{
			if (100 < it->getPos().y)
			{
				// 対応テーブルからも削除
				table.erase(it->id());

				it = bodies.erase(it);
			}
			else
			{
				++it;
			}
		}

		// 2D カメラの更新
		camera.update();
		{
			// 2D カメラから Transformer2D を作成
			const auto t = camera.createTransformer();

			// 左クリックされたら
			if (MouseL.down())
			{
				// ボディを追加
				bodies << world.createPolygons(P2Dynamic, Cursor::PosF(), polygons[index], P2Material{ 0.1, 0.0, 1.0 });

				// ボディ ID と絵文字のインデックスの組を対応テーブルに追加
				table.emplace(bodies.back().id(), std::exchange(index, Random(polygons.size() - 1)));
			}

			// すべてのボディを描画
			for (const auto& body : bodies)
			{
				textures[table[body.id()]].rotated(body.getAngle()).drawAt(body.getPos());
			}

			// 地面を描画
			ground.draw(Palette::Green);

			// 現在操作できる絵文字を描画
			textures[index].drawAt(Cursor::PosF(), AlphaF(0.5 + Periodic::Sine0_1(1s) * 0.5));
		}

		// 2D カメラの操作を描画
		camera.draw(Palette::Orange);
	}
}
