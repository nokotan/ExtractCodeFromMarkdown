# include <Siv3D.hpp>

// アイテムの情報の構造体
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
	const double spawnTime = 0.5;

	// 最後にアイテムが発生してからの経過時間（秒）
	double itemTimer = 0.0;

	// アイテムの落下スピード（ピクセル / 秒)
	const double itemSpeed = 200.0;

	// スコア (★追加★)
	int32 score = 0;

	while (System::Update())
	{
		// プログラムの状態の可視化
		ClearPrint();
		Print << U"ゲーム中のアイテムの個数: " << items.size();
		Print << U"スコア: " << score; // (★追加★)

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
			// Clamp(x, min, max) は x を min～max の範囲に収めた値を返す
			playerPos.x = Clamp(playerPos.x, 0.0, 800.0);
		}

		// アイテムの出現と移動と消滅に関する処理
		{
			itemTimer += deltaTime;

			// spawnTime が経過するごとに新しいアイテムを出現させる
			while (itemTimer >= spawnTime)
			{
				Item item;
				item.pos.x = Random(100, 700); // アイテムの X 座標
				item.pos.y = -100; // アイテムの Y 座標
				item.type = 0; // アイテムの種類。 = Random(0, 3); とすれば 0～3 のランダムな数に

				// 配列に追加
				items << item;

				itemTimer -= spawnTime;
			}

			// すべてのアイテムについて移動処理
			for (auto& item : items)
			{
				item.pos.y += deltaTime * itemSpeed;
			}

			// プレイヤーのあたり判定の円 (★追加★)
			const Circle playerCirlce{ playerPos, 60 };

			// アイテムのあたり判定と回収したアイテムの削除 (★追加★)
			for (auto it = items.begin(); it != items.end();)
			{
				// アイテムのあたり判定の円 (★追加★)
				const Circle itemCircle{ it->pos, 60 };

				// 交差したらアイテムを削除 (★追加★)
				if (playerCirlce.intersects(itemCircle))
				{
					// (削除する前に) スコアを加算 (★追加★)
					score += 100;

					// アイテムを削除 (★追加★)
					it = items.erase(it);
				}
				else
				{
					// イテレータを次のアイテムに進める (★追加★)
					++it;
				}
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

		// 当たり判定の可視化（デバッグ用） (★追加★)
		Circle{ playerPos, 60 }.drawFrame(2, Palette::Red); // プレイヤーの当たり判定円 (★追加★)
		for (const auto& item : items) // アイテムの当たり判定円 (★追加★)
		{
			Circle{ item.pos, 60 }.drawFrame(2, Palette::Red);
		}
	}
}
