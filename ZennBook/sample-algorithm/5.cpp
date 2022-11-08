# include <Siv3D.hpp>

void Main()
{
	// 画面サイズを変更
	Window::Resize(1280, 720);

	// マップの領域
	constexpr Rect mapArea{ 0, 0, 1000, 720 };

	// ナビメッシュ
	NavMesh navMesh;

	// マップの形状を表現する　Polygon
	Polygon polygon;

	// 経路
	LineString path;

	// 現在地
	Vec2 pos{ 100, 100 };

	// 目的地
	Vec2 destination{ 300, 300 };

	// 更新の必要の有無
	bool dirty = true;

	// 入力モード 0: マップ, 1: 現在地, 2: 目的地
	size_t inputMode = 0;

	while (System::Update())
	{
		// マップエリアを表示
		mapArea.draw(ColorF{ 0.2, 0.4, 0.3 });

		// マップの形状を表示（更新が必要な時はグレー）
		polygon.draw(dirty ? Palette::Gray : Palette::Yellow);
		polygon.drawWireframe(1.0, Palette::Gray);

		// マップエリア上での操作
		if (mapArea.mouseOver())
		{
			if (inputMode == 0)
			{
				const Circle shape{ Cursor::Pos(), 30 };
				shape.drawFrame(2, Palette::Skyblue);

				if (MouseL.pressed())
				{
					// マップの Polygon に円を追加
					dirty |= polygon.append(shape.asPolygon());
				}

				// カーソルは非表示
				Cursor::RequestStyle(CursorStyle::Hidden);
			}
			else if (inputMode == 1)
			{
				if (MouseL.pressed())
				{
					// 現在地を変更
					pos = Cursor::Pos();
					path = navMesh.query(pos, destination);
				}

				// カーソルは手のマーク
				Cursor::RequestStyle(CursorStyle::Hand);
			}
			else if (inputMode == 2)
			{
				if (MouseL.pressed())
				{
					// 目的地を変更
					destination = Cursor::Pos();
					path = navMesh.query(pos, destination);
				}

				// カーソルは手のマーク
				Cursor::RequestStyle(CursorStyle::Hand);
			}
		}

		// 入力モードを変更するラジオボタン
		SimpleGUI::RadioButtons(inputMode, { U"map", U"position", U"destination" }, Vec2{ 1050, 40 }, 180);

		if (SimpleGUI::Button(U"Build Path", Vec2{ 1050, 180 }, 180))
		{
			// 計算コスト削減のため Polygon を単純化
			polygon = polygon.simplified(2.0);

			// NavMesh を更新
			if (navMesh.build(polygon))
			{
				// 経路を計算
				path = navMesh.query(pos, destination);
				dirty = false;
			}
		}

		// 経路を表示
		path.draw(10, Palette::Red);

		// 現在地を表示
		RectF{ Arg::center = pos, 30 }
			.rotated(Scene::Time() * 60_deg)
			.draw((inputMode == 1) ? Palette::Red.lerp(Palette::White, Periodic::Sine0_1(1s)) : Palette::Red);

		// 目的地を表示
		Circle{ destination, 15 }
			.draw((inputMode == 2) ? Palette::Red.lerp(Palette::White, Periodic::Sine0_1(1s)) : Palette::Red);
	}
}
