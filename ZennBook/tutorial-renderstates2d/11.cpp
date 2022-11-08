# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	const Texture cat{ U"🐈"_emoji };

	// 2D カメラ
	// 初期設定: 中心 (0, 0), ズームアップ倍率 1.0
	Camera2D camera{ Vec2{ 0, 0 }, 1.0 };
	//Camera2D camera{ Vec2{ 0, 0 }, 1.0, CameraControl::Mouse }; // マウス操作のみの場合

	while (System::Update())
	{
		// 2D カメラを更新
		camera.update();
		{
			// 2D カメラの設定から Transformer2D を作成
			const auto t = camera.createTransformer();

			for (int32 i = 0; i < 8; ++i)
			{
				Circle{ 0, 0, (50 + i * 50) }.drawFrame(2);
			}

			cat.drawAt(0, 0);

			Shape2D::Star(50, Vec2{ 200, 200 }).draw(Palette::Yellow);
		}

		if (SimpleGUI::Button(U"Jump to center", Vec2{ 20, 20 }))
		{
			// 中心とズームアップ倍率を即座に変更
			camera.jumpTo(Vec2{ 0, 0 }, 1.0);
		}

		if (SimpleGUI::Button(U"Move to center", Vec2{ 20, 60 }))
		{
			// 中心とズームアップ倍率の目標値をセットして、時間をかけて変更する
			camera.setTargetCenter(Vec2{ 0, 0 });
			camera.setTargetScale(1.0);
		}

		// 2D カメラ操作の UI を表示
		camera.draw(Palette::Orange);
	}
}
