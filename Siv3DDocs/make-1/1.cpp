# include <Siv3D.hpp>

// アイテムの情報
struct Item
{
	// アイテムの現在位置
	Vec2 pos;

	// アイテムの種類を表す ID
	int32 type;
};

void Main()
{
	// プレイヤーの絵文字テクスチャ
	const Texture playerTexture{ U"😃"_emoji };

	// プレイヤーのスピード（ピクセル / 秒)
	const double playerSpeed = 500.0;

	// プレイヤーの座標
	Vec2 playerPos{ 400, 500 };

	// アイテムのテクスチャ
	const Texture itemTexture{ U"🍰"_emoji };

	// 現在画面上にあるアイテムの配列
	Array<Item> items;

	// アイテムが発生する時間間隔（秒）
	const double SpawnTime = 0.5;

	// 最後にアイテムが発生してからの経過時間（秒）
	double itemTimer = 0.0;

	// アイテムの落下スピード（ピクセル / 秒) 
	const double ItemSpeed = 200.0;

	while (System::Update())
	{
		// アイテムの個数の可視化
		ClearPrint();
		Print << U"ゲーム中のアイテムの個数: " << items.size();

		////////////////////////////////
		//
		//	状態更新
		//
		////////////////////////////////

		// 前のフレームからの経過時間 (秒)
		const double deltaTime = Scene::DeltaTime();

		// プレイヤーの移動に関する処理
		{
			if (KeyLeft.pressed()) // [←] キーが押されていたら
			{
				playerPos.x -= (playerSpeed * deltaTime);
			}
			else if (KeyRight.pressed()) // [→] キーが押されていたら
			{
				playerPos.x += (playerSpeed * deltaTime);
			}

			// 壁の外に出ないようにする
			// Clamp(x, min, max) は, x を min～max の範囲に収めた値を返す
			playerPos.x = Clamp(playerPos.x, 0.0, 800.0);
		}

		// アイテムの出現と移動と消滅に関する処理
		{
			itemTimer += deltaTime;

			// spawnTime が経過するごとに新しいアイテムを出現させる
			while (itemTimer >= SpawnTime)
			{
				Item item;
				item.pos.x = Random(100, 700); // アイテムの X 座標
				item.pos.y = -100; // アイテムの Y 座標
				item.type = 0; // アイテムの種類。 = Random(0, 3); とすれば 0～3 のランダムな数に

				// 配列に追加
				items << item;

				itemTimer -= SpawnTime;
			}

			// すべてのアイテムについて移動処理
			for (auto& item : items)
			{
				item.pos.y += deltaTime * ItemSpeed;
			}

			// 画面外に出たアイテムを消去する
			items.remove_if([](const Item& item) { return (item.pos.y > 700); });
		}

		////////////////////////////////
		//
		//	描画
		//
		////////////////////////////////

		// 背景はグラデーションの Rect
		Scene::Rect()
			.draw(Arg::top = ColorF{ 0.1, 0.4, 0.8 }, Arg::bottom = ColorF{ 0.3, 0.7, 1.0 });

		// プレイヤーのテクスチャの描画
		playerTexture.drawAt(playerPos);

		// アイテムの描画
		for (const auto& item : items)
		{
			itemTexture.drawAt(item.pos);
		}
	}
}
