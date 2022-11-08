# include <Siv3D.hpp>

void Main()
{
	// ウィンドウを 1280x720 にリサイズ
	Window::Resize(1280, 720);

	// 背景色を設定
	Scene::SetBackground(ColorF{ 0.4, 0.7, 1.0 });

	// 2D 物理演算のシミュレーションステップ（秒）
	constexpr double stepSec = (1.0 / 200.0);

	// 2D 物理演算のシミュレーション蓄積時間（秒）
	double accumulatorSec = 0.0;

	// 2D 物理演算のワールド
	P2World world;

	// [_] 地面
	const P2Body ground = world.createLine(P2Static, Vec2{ 0, 0 }, Line{ -1600, 0, 1600, 0 });

	// [■] 箱 (Sleep させておく)
	Array<P2Body> boxes;
	{
		for (auto y : Range(0, 12))
		{
			for (auto x : Range(0, 20))
			{
				boxes << world.createRect(P2Dynamic, Vec2{ x * 50, -50 - y * 100 },
					SizeF{ 50, 100 }, P2Material{ .density = 0.02, .restitution = 0.0, .friction = 1.0 })
					.setAwake(false);
			}
		}
	}

	// 振り子の軸の座標
	constexpr Vec2 pivotPos{ 0, -2400 };

	// チェーンを構成するリンク 1 つの長さ
	constexpr double linkLength = 100.0;

	// チェーンを構成するリンクの数
	constexpr int32 linkCount = 16;

	// チェーンの長さ
	constexpr double chainLength = (linkLength * linkCount);

	// 鉄球の半径
	constexpr double ballR = 200;

	// 鉄球の初期座標
	constexpr Vec2 ballCenter = pivotPos.movedBy(-chainLength - ballR, 0);

	// [●] 鉄球
	const P2Body ball = world.createCircle(P2BodyType::Dynamic, ballCenter, ballR,
		P2Material{ .density = 0.5, .restitution = 0.0, .friction = 1.0 });

	// [ ] 振り子の軸（実体がないプレースホルダー）
	const P2Body pivot = world.createPlaceholder(P2BodyType::Static, pivotPos);

	// [-] チェーンを構成するリンク
	Array<P2Body> links;

	// リンクどうしやリンクと鉄球をつなぐジョイント
	Array<P2PivotJoint> joints;
	{
		for (auto i : step(linkCount))
		{
			// リンクの長方形（隣接するリンクと重なるよう少し大きめに）
			const RectF rect{ Arg::rightCenter = pivotPos.movedBy(i * -linkLength, 0), linkLength * 1.2, 20 };

			// categoryBits を 0 にすることで、箱など他の物体と干渉しないようにする
			links << world.createRect(P2Dynamic, rect.center(), rect.size,
				P2Material{ .density = 0.1, .restitution = 0.0, .friction = 1.0 }, P2Filter{ .categoryBits = 0 });

			if (i == 0)
			{
				// 振り子の軸と最初のリンクをつなぐジョイント
				joints << world.createPivotJoint(pivot, links.back(), rect.rightCenter().movedBy(-linkLength * 0.1, 0));
			}
			else
			{
				// 新しいリンクと、一つ前のリンクをつなぐジョイント
				joints << world.createPivotJoint(links[links.size() - 2], links.back(), rect.rightCenter().movedBy(-linkLength * 0.1, 0));
			}
		}

		// 最後のリンクと鉄球をつなぐジョイント
		joints << world.createPivotJoint(links.back(), ball, pivotPos.movedBy(-chainLength, 0));
	}

	// [/] ストッパー
	P2Body stopper = world.createLine(P2Static, ballCenter.movedBy(0, 200), Line{ -400, 200, 400, 0 });

	// 2D カメラ
	Camera2D camera{ Vec2{ 0, -1200 }, 0.25 };

	while (System::Update())
	{
		for (accumulatorSec += Scene::DeltaTime(); stepSec <= accumulatorSec; accumulatorSec -= stepSec)
		{
			// 2D 物理演算のワールドを更新
			world.update(stepSec);

			// 落下した box は削除
			boxes.remove_if([](const P2Body& body) { return (2000 < body.getPos().y); });
		}

		// 2D カメラの更新
		camera.update();
		{
			// 2D カメラから Transformer2D を作成
			const auto t = camera.createTransformer();

			// 地面を描く
			ground.draw(ColorF{ 0.0, 0.5, 0.0 });

			// チェーンを描く
			for (const auto& link : links)
			{
				link.draw(ColorF{ 0.25 });
			}

			// 箱を描く
			for (const auto& box : boxes)
			{
				box.draw(ColorF{ 0.6, 0.4, 0.2 });
			}

			// ストッパーを描く
			stopper.draw(ColorF{ 0.25 });

			// 鉄球を描く
			ball.draw(ColorF{ 0.25 });
		}

		// ストッパーを無くす
		if (stopper && SimpleGUI::Button(U"Go", Vec2{ 1100, 20 }))
		{
			// ストッパーを破棄
			stopper.release();
		}

		// 2D カメラの操作を描画
		camera.draw(Palette::Orange);
	}
}
