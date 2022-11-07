# include <Siv3D.hpp>

void Main()
{
	Window::Resize(1280, 720);

	Scene::SetBackground(ColorF{ 0.94, 0.91, 0.86 });

	const Font font{ 100, Typeface::Bold };

	// 2D 物理演算のシミュレーションステップ（秒）
	constexpr double stepSec = (1.0 / 200.0);

	// 2D 物理演算のシミュレーション蓄積時間（秒）
	double accumulatorSec = 0.0;

	// 物理演算のワールド
	P2World world;

	// 床
	const P2Body line = world.createLine(P2Static, Vec2{ 0, 0 }, Line{ -1600, 0, 1600, 0 }, OneSided::Yes, P2Material{ 1.0, 0.1, 1.0 });

	// 文字のパーツ
	Array<P2Body> bodies;

	String text;
	int32 generation = 0;
	HashTable<P2BodyID, int32> table;

	// 2D カメラ
	Camera2D camera{ Vec2{ 0, -500 }, 0.38, Camera2DParameters::MouseOnly() };

	constexpr Vec2 textPos{ -400, -500 };

	while (System::Update())
	{
		for (accumulatorSec += Scene::DeltaTime(); stepSec <= accumulatorSec; accumulatorSec -= stepSec)
		{
			// 2D 物理演算のワールドを更新
			world.update(stepSec);
		}

		// 2D カメラの更新
		camera.update();

		// テキストの入力
		TextInput::UpdateText(text);

		{
			// 2D カメラを適用する Transformer2D の作成
			const auto t = camera.createTransformer();

			// 世代に応じた色で Body を描画
			for (const auto& body : bodies)
			{
				body.draw(HSV{ (table[body.id()] * 45 + 30), 0.8, 0.8 });
			}

			// 床を描画
			line.draw(Palette::Green);

			const String currentText = (text + TextInput::GetEditingText());

			// 入力文字を描画
			{
				const Transformer2D scaling(Mat3x2::Scale(2.5));

				font(currentText).draw(textPos, ColorF{ 0.5 });
			}

			// 改行文字が入力されたらテキストを P2Body にする
			if (currentText.includes(U'\n'))
			{
				// 入力文字を PolygonGlyph 化
				const Array<PolygonGlyph> glyphs = font.renderPolygons(currentText.removed(U'\n'));

				// P2Body にする Polygon を得る
				Array<Polygon> polygons;
				{
					Vec2 penPos{ textPos };

					for (const auto& glyph : glyphs)
					{
						for (const auto& polygon : glyph.polygons)
						{
							polygons << polygon
								.movedBy(penPos + glyph.getOffset())
								.scaled(2.5)
								.simplified(2.0);
						}

						penPos.x += glyph.xAdvance;
					}
				}

				for (const auto& polygon : polygons)
				{
					bodies << world.createPolygon(P2Dynamic, Vec2{ 0, 0 }, polygon, P2Material{ 1, 0.0, 0.4 });

					// 現在の世代を保存
					table[bodies.back().id()] = generation;
				}

				text.clear();

				// 世代を進める
				++generation;
			}

			// 2D カメラ、右クリック時の UI を表示
			camera.draw(Palette::Orange);
		}

		// 消去ボタン
		if (SimpleGUI::Button(U"Clear", Vec2{ 1100, 40 }))
		{
			bodies.clear();
		}
	}
}
